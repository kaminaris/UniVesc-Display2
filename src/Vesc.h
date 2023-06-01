#ifndef LUMIA_ESP32_VESC_H
#define LUMIA_ESP32_VESC_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "VescUart.h"
#include "WireBus.h"
#include "VescSettings.h"
#include "AppSerial.h"

#define RXD2 14
#define TXD2 11


#define GEAR_RATIO (settings.motorPulley / settings.wheelPulley)

enum AppMode { Demo, Live };

class Vesc {
	public:
	float tachometer = 0;
	float rpm = 0;
	float distance = 0;
	double velocity = 0;
	float batPercentage = 0;
	float motorTemp = 0;
	float mosfetTemp = 0;
	float powerWatt = 0;
	float powerPercent = 0;
	float voltage = 0;
	float duty = 0;
	float wattHours = 0;

	// calculated values, not saved
	float avgSpeed = 0;
	float origOdo = 0;

	// settings
	struct VescSettings origSettings = {};
	struct VescSettings settings = {};

	bool loadRequested = false;
	bool saveRequested = false;
	AppMode mode = Demo;

	VescUart* vescUart = nullptr;

	void init();
	void read();

	void load();
	void save();

	void loadInternal();
	void saveInternal();
	void resetSettings();
};

#endif
