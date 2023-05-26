#define LGFX_USE_V1
// #define LGFX_AUTODETECT // Autodetect board

#include <Arduino.h>
#include <LGFXCustom.h>
#include <lvgl.h>
#include <pgmspace.h>

#include <LovyanGFX.hpp>

#include "Vesc.h"
#include "WireBus.h"
#include "ui/ui.h"

#define TFT_RST 4
#define TFT_CS -1
#define TFT_BL 45

// #define I2C_SDA 6
// #define I2C_SCL 5
#define RST_N_PIN -1
#define INT_N_PIN 7

#define SCR 30

#define MUSIC_PLAYER

#define SD_CS 41
#define SDMMC_CMD 40
#define SDMMC_CLK 39
#define SDMMC_D0 38

#define I2S_DOUT 37
#define I2S_BCLK 36
#define I2S_LRC 35

long timeout;

/* Change to your screen resolution */
static const uint32_t screenWidth = 320;
static const uint32_t screenHeight = 480;

static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;

uint8_t brightness = 200;

// Create an instance of the prepared class.
LGFXCustom tft;

static lv_color_t disp_draw_buf[screenWidth * SCR];
static lv_color_t disp_draw_buf2[screenWidth * SCR];

Vesc vesc;

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

[[noreturn]] void lvglLoop(void* parameter) {
	while (true) {
		lv_timer_handler();
		delay(5);
	}

	vTaskDelete(nullptr);
}

void guiHandler() {
	xTaskCreatePinnedToCore(lvglLoop, "LVGL Loop", 16384, nullptr, 1, nullptr, 1);
}

[[noreturn]] void readVescTask(void* pvParameters) {
	while (true) {
		vesc.read();

		lv_bar_set_value(ui_batteryBar, vesc.batPercentage, LV_ANIM_OFF);
		lv_color_t batteryColor =
			lv_color_make(255 - 255 * vesc.batPercentage / 100, 255 * vesc.batPercentage / 100, 0);
		lv_obj_set_style_bg_color(ui_batteryBar, batteryColor, LV_PART_INDICATOR);
		lv_label_set_text(ui_batteryPercentage, (String(vesc.batPercentage, 0) + "%").c_str());
		lv_label_set_text(ui_speed, String(vesc.velocity, 0).c_str());
		lv_arc_set_value(ui_speedGauge, vesc.velocity);
		lv_label_set_text(ui_motorTemp, (String(vesc.motorTemp, 1) + "°C").c_str());
		lv_label_set_text(ui_mosfetTemp, (String(vesc.mosfetTemp, 1) + "°C").c_str());
		lv_label_set_text(ui_batteryVoltage, (String(vesc.voltage, 1) + "V").c_str());
		lv_label_set_text(ui_duty, (String(vesc.duty, 0) + "%").c_str());
		lv_label_set_text(ui_trip, (String(vesc.distance, 1) + "km").c_str());
		lv_label_set_text(ui_odo, (String(vesc.odo, 1) + "km").c_str());
		lv_label_set_text(ui_maxSpeed, (String(vesc.maxSpeed, 1) + "km/h").c_str());
		lv_label_set_text(ui_avgSpeed, (String(vesc.avgSpeed, 1) + "km/h").c_str());

		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

[[noreturn]] void wireBusReadTask(void* p) {
	while (true) {
		WireBus::getTime();
		lv_label_set_text(ui_clock, WireBus::timeString);

		if (vesc.loadRequested) {
			vesc.loadInternal();
		}

		if (vesc.saveRequested) {
			vesc.saveInternal();
		}
		vTaskDelay(pdMS_TO_TICKS(400));
	}
}

void setup() {
	Serial.begin(115200);

	tft.init();
	tft.initDMA();
	tft.startWrite();

	pinMode(SD_CS, OUTPUT);
	digitalWrite(SD_CS, HIGH);

	// NVS.begin();
	vesc.init();
	vesc.load();

	WireBus::init();
	lv_init();

	Serial.print("Width: ");
	Serial.print(screenWidth);
	Serial.print("\tHeight: ");
	Serial.println(screenHeight);

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

	guiHandler();

	tft.setBrightness(brightness);

	xTaskCreatePinnedToCore(readVescTask, "ReadVesc", 8192, nullptr, 5, nullptr, ARDUINO_RUNNING_CORE);
	xTaskCreatePinnedToCore(wireBusReadTask, "WireRead", 8192, nullptr, 6, nullptr, ARDUINO_RUNNING_CORE);

	uint64_t mac = ESP.getEfuseMac();

	String info = "";

	info += "\nChip model: " + String(ESP.getChipModel());
	info += "\nChip cores: " + String(ESP.getChipCores());
	info += "\nChip frequency: " + String(ESP.getCpuFreqMHz()) + "Mhz";
	info += "\nChip version: " + String(ESP.getChipRevision());

	info += "\nRAM size: " + String((ESP.getHeapSize() / 1024.0), 0) + "kB";
	info += "\nPSRAM size: " + String((ESP.getPsramSize() / (1024.0 * 1024.0)), 0) + "MB";

	info += "\nFlash size: " + String((ESP.getFlashChipSize() / (1024.0 * 1024.0)), 0) + "MB";
	info += "\nFlash speed: " + String((ESP.getFlashChipSpeed() / 1000000.0), 0) + "Mhz";

	info += "\nSDK version: " + String(ESP.getSdkVersion());
	info += "\nFirmware size: " + String((ESP.getSketchSize() / (1024.0 * 1024.0)), 0) + "MB";
	info += "\nMAC address: ";

	for (int i = 0; i < 6; i++) {
		if (i > 0) {
			info += "-";
		}
		info += String(byte(mac >> (i * 8) & 0xFF), HEX);
	}

	Serial.println(info);

	Serial.println("Device ready");
}

bool lossOccurred = false;
void loop() {
	int sensorValue = analogRead(10);
	if (sensorValue < 2700 && !lossOccurred && vesc.mode == Live) {
		vesc.saveInternal();
		Serial.printf("power loss occured %d\n", sensorValue);
		lossOccurred = true;
	}

	delay(1);
}
