#ifndef LUMIA_ESP32_LGFX_H
#define LUMIA_ESP32_LGFX_H

#include <lvgl.h>
#include "ui/ui.h"
#include <LovyanGFX.hpp>

#define SCR 30

/* Change to your screen resolution */
static const uint32_t screenWidth = 320;
static const uint32_t screenHeight = 480;

static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;

static lv_color_t disp_draw_buf[screenWidth * SCR];
static lv_color_t disp_draw_buf2[screenWidth * SCR];

uint8_t brightness = 200;

class LGFXCustom : public lgfx::LGFX_Device {
	lgfx::Panel_ST7796 _panel_instance;
	lgfx::Bus_Parallel8 _bus_instance;
	lgfx::Light_PWM _light_instance;
	lgfx::Touch_FT5x06 _touch_instance;

	public:
	LGFXCustom() {
		{
			auto cfg = _bus_instance.config();

			cfg.port = 0;
			cfg.freq_write = 20000000;
			cfg.pin_wr = 47;  // pin connecting WR
			cfg.pin_rd = -1;  // pin connecting RD
			cfg.pin_rs = 0;	  // pin connecting RS(D/C)
			cfg.pin_d0 = 9;	  // pin connecting D0
			cfg.pin_d1 = 46;  // pin connecting D1
			cfg.pin_d2 = 3;	  // pin connecting D2
			cfg.pin_d3 = 8;	  // pin connecting D3
			cfg.pin_d4 = 18;  // pin connecting D4
			cfg.pin_d5 = 17;  // pin connecting D5
			cfg.pin_d6 = 16;  // pin connecting D6
			cfg.pin_d7 = 15;  // pin connecting D7

			_bus_instance.config(cfg);				 // Apply the settings to the bus.
			_panel_instance.setBus(&_bus_instance);	 // Sets the bus to the panel.
		}

		{										  // Set display panel control.
			auto cfg = _panel_instance.config();  // Get the structure for display panel settings.

			cfg.pin_cs = -1;	// pin to which CS is connected (-1 = disable)
			cfg.pin_rst = 4;	// pin where RST is connected (-1 = disable)
			cfg.pin_busy = -1;	// pin to which BUSY is connected (-1 = disable)

			// * The following setting values ​​are set to general default values ​​for each panel, and the pin
			// number (-1 = disable) to which BUSY is connected, so please try commenting out any unknown items.

			cfg.memory_width = 320;	  // Maximum width supported by driver IC
			cfg.memory_height = 480;  // Maximum height supported by driver IC
			cfg.panel_width = 320;	  // actual displayable width
			cfg.panel_height = 480;	  // actual displayable height
			cfg.offset_x = 0;		  // Panel offset in X direction
			cfg.offset_y = 0;		  // Panel offset in Y direction
			cfg.offset_rotation = 0;
			cfg.dummy_read_pixel = 8;
			cfg.dummy_read_bits = 1;
			cfg.readable = false;
			cfg.invert = true;
			cfg.rgb_order = false;
			cfg.dlen_16bit = false;
			cfg.bus_shared = true;

			_panel_instance.config(cfg);
		}

		{										  // Set backlight control. (delete if not necessary)
			auto cfg = _light_instance.config();  // Get the structure for backlight configuration.

			cfg.pin_bl = 45;	  // pin to which the backlight is connected
			cfg.invert = false;	  // true to invert backlight brightness
			cfg.freq = 44100;	  // backlight PWM frequency
			cfg.pwm_channel = 0;  // PWM channel number to use

			_light_instance.config(cfg);
			_panel_instance.setLight(&_light_instance);	 // Sets the backlight to the panel.
		}

		{  // Configure settings for touch screen control. (delete if not necessary)
			auto cfg = _touch_instance.config();

			cfg.x_min = 0;	  // Minimum X value (raw value) obtained from the touchscreen
			cfg.x_max = 319;  // Maximum X value (raw value) obtained from the touchscreen
			cfg.y_min = 0;	  // Minimum Y value obtained from touchscreen (raw value)
			cfg.y_max = 479;  // Maximum Y value (raw value) obtained from the touchscreen
			cfg.pin_int = 7;  // pin to which INT is connected
			cfg.bus_shared = false;
			cfg.offset_rotation = 0;

			// For I2C connection
			cfg.i2c_port = 0;	  // Select I2C to use (0 or 1)
			cfg.i2c_addr = 0x38;  // I2C device address number
			cfg.pin_sda = 6;	  // pin where SDA is connected
			cfg.pin_scl = 5;	  // pin to which SCL is connected
			cfg.freq = 400000;	  // set I2C clock

			_touch_instance.config(cfg);
			_panel_instance.setTouch(&_touch_instance);	 // Set the touchscreen to the panel.
		}

		setPanel(&_panel_instance);	 // Sets the panel to use.
	}

	[[noreturn]] static void lvglLoop(void* parameter) {
		while (true) {
			lv_timer_handler();
			delay(5);
		}

		vTaskDelete(nullptr);
	}

	void guiHandler() {
		xTaskCreatePinnedToCore(LGFXCustom::lvglLoop, "LVGL Loop", 16384, nullptr, 1, nullptr, 1);
	}
};

// Create an instance of the prepared class.
LGFXCustom tft;

/* Display flushing */
void my_disp_flush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p) {
	if (tft.getStartCount() == 0) {
		tft.endWrite();
	}

	tft.pushImageDMA(
		area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (lgfx::swap565_t*)&color_p->full
	);

	lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
}

/* Read the touchpad */
void my_touchpad_read(lv_indev_drv_t* indev_driver, lv_indev_data_t* data) {
	uint16_t touchX, touchY;

	bool touched = tft.getTouch(&touchX, &touchY);

	if (!touched) {
		data->state = LV_INDEV_STATE_REL;
	}
	else {
		data->state = LV_INDEV_STATE_PR;

		/*Set the coordinates*/
		data->point.x = touchX;
		data->point.y = touchY;
	}
}

void tftSetup() {
	if (!disp_draw_buf) {
		Serial.println("LVGL disp_draw_buf allocate failed!");
	}
	else {
		Serial.print("Display buffer size: ");

		lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, disp_draw_buf2, screenWidth * SCR);

		/* Initialize the display */
		lv_disp_drv_init(&disp_drv);
		/* Change the following line to your display resolution */
		disp_drv.hor_res = screenWidth;
		disp_drv.ver_res = screenHeight;
		disp_drv.flush_cb = my_disp_flush;
		disp_drv.draw_buf = &draw_buf;
		lv_disp_drv_register(&disp_drv);

		/* Initialize the input device driver */
		static lv_indev_drv_t indev_drv;
		lv_indev_drv_init(&indev_drv);
		indev_drv.type = LV_INDEV_TYPE_POINTER;
		indev_drv.read_cb = my_touchpad_read;
		lv_indev_drv_register(&indev_drv);

		ui_init();

		Serial.println("Setup done");
	}

	tft.guiHandler();

	tft.setBrightness(brightness);
}
#endif
