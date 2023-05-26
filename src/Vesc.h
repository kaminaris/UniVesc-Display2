#ifndef LUMIA_ESP32_VESC_H
#define LUMIA_ESP32_VESC_H

#include <Arduino.h>
#include <SoftwareSerial.h>

#include "VescUart.h"
#include "WireBus.h"

#define RXD2 14
#define TXD2 11

#define WHEEL_DIAMETER 0.5 // in meters
#define MOTOR_PULLEY 1.0
#define WHEEL_PULLEY 1.0
#define MOTOR_POLE_PAIRS 30.0
#define MAX_BATTERY_VOLTAGE 84.0
#define MIN_BATTERY_VOLTAGE 50.0
#define MAX_MOTOR_CURRENT 35.0

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

	float maxSpeed = 0;
	float avgSpeed = 0;
	float odo = 0;
	float origOdo = 0;
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
};

#endif
