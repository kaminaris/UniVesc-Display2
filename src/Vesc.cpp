#include "Vesc.h"

#define NO_DEMO 1

void Vesc::init() {
	Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
	vescUart = new VescUart(300);
	vescUart->setSerialPort(&Serial2);
	// vescUart->setDebugPort(&Serial);
}

void Vesc::read() {
	if (vescUart->getVescValues()) {
		motorTemp = vescUart->data.tempMotor;
		mosfetTemp = vescUart->data.tempMosfet;
		duty = abs(vescUart->data.dutyCycleNow) * 100;
		wattHours = vescUart->data.wattHours;

		voltage = vescUart->data.inpVoltage;
		powerPercent = abs(vescUart->data.avgMotorCurrent / settings.maxMotorCurrent);
		powerWatt = vescUart->data.avgMotorCurrent * voltage;

		// Code borrowed from
		// https://github.com/TomStanton/VESC_LCD_EBIKE/blob/master/VESC6_LCD_EBIKE.ino

		// This is the number of motor poles multiplied by 3
		tachometer = vescUart->data.tachometerAbs / (settings.motorPolePairs * 2 * 3);

		rpm = vescUart->data.rpm / settings.motorPolePairs;

		// Motor tacho x Pi x (1 / meters in a mile or km) x Wheel diameter x gear ratio
		distance = tachometer * PI * (1.0 / 1000.0) * settings.wheelDiameter * GEAR_RATIO;

		// Motor RPM x Pi x (seconds in a minute / meters in a kilometer) x Wheel diameter x gear ratio
		velocity = rpm * PI * settings.wheelDiameter * (60.0 / 1000.0) * GEAR_RATIO;

		// ((Battery voltage - minimum voltage) / number of cells) x 100
		batPercentage = 100 * (vescUart->data.inpVoltage - settings.minBatteryVoltage) /
						(settings.maxBatteryVoltage - settings.minBatteryVoltage);

		settings.odo = floor(origOdo + distance);
		avgSpeed = distance / (millis() / 1000.0 / 3600.0);

		if (velocity > settings.maxSpeed) {
			settings.maxSpeed = velocity;
			save();
		}

		mode = Live;
		connected = true;
	}
	else {
		connected = false;
		// appSerial.println("Failed to get data!");
#ifndef NO_DEMO
		velocity = random(60);
		voltage = random(MAX_BATTERY_VOLTAGE * 10) / 10;
		batPercentage = random(100);
		powerWatt = random(2200);
		powerPercent = random(100);
		motorTemp = random(500) / 10;
		mosfetTemp = random(500) / 10;

		mode = Demo;
#endif
	}
}

void Vesc::load() {
	loadRequested = true;
}

void Vesc::resetSettings() {
	settings = {};
}

void Vesc::loadInternal() {
	WireBus::read(0, (u8_t*)&settings, sizeof settings);

	if (isnan(settings.motorPolePairs) || settings.motorPolePairs == 0) {
		settings = {};
	}

	appSerial.printf(
		"loaded %f, %f, %f, %f, %f, %f, %f",
		settings.motorPolePairs,
		settings.minBatteryVoltage,
		settings.maxBatteryVoltage,
		settings.wheelDiameter,
		settings.maxSpeed,
		settings.odo,
		settings.motorPulley
	);
	origOdo = settings.odo;
	loadRequested = false;
}

void Vesc::save() {
	saveRequested = true;
}

void Vesc::saveInternal() {
	u8_t* current = (u8_t*)&settings;
	u8_t* original = (u8_t*)&origSettings;
	for (unsigned int i = 0; i < sizeof(settings); i++) {
		u8_t origB = (u8_t) * (original + i);
		u8_t currentB = (u8_t) * (current + i);

		if (origB != currentB) {
			WireBus::write(i, currentB);
			appSerial.printf("saving %d %d", i, currentB);
		}
	}

	// sync orig settings since they were saved
	memcpy((void*)&origSettings, (void*)&settings, sizeof settings);
	appSerial.printf(
		"saved %f, %f, %f, %f, %f, %f, %f",
		settings.motorPolePairs,
		settings.minBatteryVoltage,
		settings.maxBatteryVoltage,
		settings.wheelDiameter,
		settings.maxSpeed,
		settings.odo,
		settings.motorPulley
	);
	saveRequested = false;
}
