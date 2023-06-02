#define LGFX_USE_V1

#include <Arduino.h>
#include <LGFXCustom.h>
#include <lvgl.h>

#include "AppSerial.h"
#include "Vesc.h"
#include "WireBus.h"
#include "ui/ui.h"
#include "SoundPlayer.h"

#define SD_CS 41
#define SDMMC_CMD 40
#define SDMMC_CLK 39
#define SDMMC_D0 38

bool lossOccurred = false;

Vesc vesc;

[[noreturn]] void readVescTask(__unused void* pvParameters) {
	while (true) {
		vesc.read();

		lv_bar_set_value(ui_batteryBar, (int)vesc.batPercentage, LV_ANIM_OFF);
		lv_color_t batteryColor =
			lv_color_make(255 - 255 * vesc.batPercentage / 100, 255 * vesc.batPercentage / 100, 0);
		lv_obj_set_style_bg_color(ui_batteryBar, batteryColor, LV_PART_INDICATOR);
		lv_label_set_text(ui_batteryPercentage, (String(vesc.batPercentage, 0) + "%").c_str());
		lv_label_set_text(ui_speed, String(vesc.velocity, 0).c_str());
		lv_arc_set_value(ui_speedGauge, (short)abs(vesc.velocity));
		lv_label_set_text(ui_motorTemp, (String(vesc.motorTemp, 1) + "°C").c_str());
		lv_label_set_text(ui_mosfetTemp, (String(vesc.mosfetTemp, 1) + "°C").c_str());
		lv_label_set_text(ui_batteryVoltage, (String(vesc.voltage, 1) + "V").c_str());
		lv_label_set_text(ui_duty, (String(vesc.duty, 0) + "%").c_str());
		lv_label_set_text(ui_trip, (String(vesc.distance, 1) + "km").c_str());
		lv_label_set_text(ui_odo, (String(vesc.settings.odo, 0) + "km").c_str());
		lv_label_set_text(ui_maxSpeed, (String(vesc.settings.maxSpeed, 0) + "km/h").c_str());
		lv_label_set_text(ui_avgSpeed, (String(vesc.avgSpeed, 0) + "km/h").c_str());

		vTaskDelay(pdMS_TO_TICKS(500));
	}
}

[[noreturn]] void wireBusReadTask(__unused void* p) {
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

	vesc.init();
	vesc.load();

	WireBus::init();
	lv_init();

	appSerial.print("Width: ");
	appSerial.print(screenWidth);
	appSerial.print("\tHeight: ");
	appSerial.println(screenHeight);

	tftSetup();

	xTaskCreatePinnedToCore(readVescTask, "ReadVesc", 8192, nullptr, 5, nullptr, ARDUINO_RUNNING_CORE);
	xTaskCreatePinnedToCore(wireBusReadTask, "WireRead", 8192, nullptr, 6, nullptr, ARDUINO_RUNNING_CORE);

	AppSerial::setup();

	if (!SPIFFS.begin()) {
		Serial.println("SPIFFS Mount Failed");
		//return;
	}

	SoundPlayer::init();

	appSerial.println("Device ready");
}

void loop() {
	int sensorValue = analogRead(10);
	if (sensorValue < 2700 && !lossOccurred && vesc.mode == Live) {
		vesc.saveInternal();
		appSerial.printf("power loss occurred %d\n", sensorValue);
		lossOccurred = true;
	}

	vTaskDelay(pdMS_TO_TICKS(100));
}
