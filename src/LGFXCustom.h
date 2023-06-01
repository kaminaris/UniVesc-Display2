#ifndef LUMIA_ESP32_LGFX_H
#define LUMIA_ESP32_LGFX_H

#include <lvgl.h>
#include "ui/ui.h"
#include "AppSerial.h"
#include <LovyanGFX.hpp>

#define SCR 30

/* Change to your screen resolution */
static const uint32_t screenWidth = 320;
static const uint32_t screenHeight = 480;

static lv_disp_draw_buf_t drawingBuffer;
static lv_disp_drv_t displayDriver;

static lv_color_t displayDrawBuffer[screenWidth * SCR];
static lv_color_t displayDrawBuffer2[screenWidth * SCR];

uint8_t brightness = 200;

class LGFXCustom : public lgfx::LGFX_Device {
	lgfx::Panel_ST7796 panelInstance;
	lgfx::Bus_Parallel8 busInstance;
	lgfx::Light_PWM lightInstance;
	lgfx::Touch_FT5x06 touchInstance;

	public:
	LGFXCustom() {
		{
			auto cfg = busInstance.config();

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

			busInstance.config(cfg);				 // Apply the settings to the bus.
			panelInstance.setBus(&busInstance);	 // Sets the bus to the panel.
		}

		{										  // Set display panel control.
			auto cfg = panelInstance.config();  // Get the structure for display panel settings.

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

			panelInstance.config(cfg);
		}

		{										  // Set backlight control. (delete if not necessary)
			auto cfg = lightInstance.config();  // Get the structure for backlight configuration.

			cfg.pin_bl = 45;	  // pin to which the backlight is connected
			cfg.invert = false;	  // true to invert backlight brightness
			cfg.freq = 44100;	  // backlight PWM frequency
			cfg.pwm_channel = 0;  // PWM channel number to use

			lightInstance.config(cfg);
			panelInstance.setLight(&lightInstance);	 // Sets the backlight to the panel.
		}

		{  // Configure settings for touch screen control. (delete if not necessary)
			auto cfg = touchInstance.config();

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

			touchInstance.config(cfg);
			panelInstance.setTouch(&touchInstance);	 // Set the touchscreen to the panel.
		}

		setPanel(&panelInstance);	 // Sets the panel to use.
	}

	[[noreturn]] static void lvglLoop(void* parameter) {
		while (true) {
			lv_timer_handler();
			vTaskDelay(pdMS_TO_TICKS(5));
		}

		vTaskDelete(nullptr);
	}

	static void guiHandler() {
		xTaskCreatePinnedToCore(LGFXCustom::lvglLoop, "LVGL Loop", 16384, nullptr, 1, nullptr, 1);
	}
};

// Create an instance of the prepared class.
LGFXCustom tft;

/* Display flushing */
void customDisplayFlush(lv_disp_drv_t* display, const lv_area_t* area, lv_color_t* color_p) {
	if (tft.getStartCount() == 0) {
		tft.endWrite();
	}

	tft.pushImageDMA(
		area->x1, area->y1, area->x2 - area->x1 + 1, area->y2 - area->y1 + 1, (lgfx::swap565_t*)&color_p->full
	);

	lv_disp_flush_ready(display); /* tell lvgl that flushing is done */
}

/* Read the touchpad */
void customTouchpadRead(lv_indev_drv_t* inputDeviceDriver, lv_indev_data_t* data) {
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
	if (!displayDrawBuffer) {
		appSerial.println("LVGL disp_draw_buf allocate failed!");
	}
	else {
		appSerial.print("Display buffer size: ");

		lv_disp_draw_buf_init(&drawingBuffer, displayDrawBuffer, displayDrawBuffer2, screenWidth * SCR);

		/* Initialize the display */
		lv_disp_drv_init(&displayDriver);
		/* Change the following line to your display resolution */
		displayDriver.hor_res = screenWidth;
		displayDriver.ver_res = screenHeight;
		displayDriver.flush_cb = customDisplayFlush;
		displayDriver.draw_buf = &drawingBuffer;
		lv_disp_drv_register(&displayDriver);

		/* Initialize the input device driver */
		static lv_indev_drv_t inputDeviceDriver;
		lv_indev_drv_init(&inputDeviceDriver);
		inputDeviceDriver.type = LV_INDEV_TYPE_POINTER;
		inputDeviceDriver.read_cb = customTouchpadRead;
		lv_indev_drv_register(&inputDeviceDriver);

		ui_init();

		appSerial.println("Setup done");
	}

	LGFXCustom::guiHandler();

	tft.setBrightness(brightness);
}
#endif
