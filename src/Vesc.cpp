#include "Vesc.h"

#define NO_DEMO 1

EspSoftwareSerial::UART testSerial;

void Vesc::init() {
	// Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
	testSerial.begin(115200, EspSoftwareSerial::SWSERIAL_8N1, RXD2, TXD2);
	vescUart = new VescUart(300);
	vescUart->setSerialPort(&testSerial);
	// vescUart->setDebugPort(&Serial);
}

void Vesc::read() {
	if (vescUart->getVescValues()) {
		// Serial.println(vescUart->data.rpm);
		// Serial.println(vescUart->data.inpVoltage);
		// Serial.println(vescUart->data.ampHours);
		// Serial.println(vescUart->data.tachometerAbs);
		// Serial.println(vescUart->data.tempMosfet);
		// Serial.println(vescUart->data.tempMotor);
		// Serial.println(vescUart->appData.pitch);
		// Serial.println(vescUart->appData.roll);

		motorTemp = vescUart->data.tempMotor;
		mosfetTemp = vescUart->data.tempMosfet;
		duty = abs(vescUart->data.dutyCycleNow);
		wattHours = vescUart->data.wattHours;

		voltage = vescUart->data.inpVoltage;
		powerPercent = abs(vescUart->data.avgMotorCurrent / MAX_MOTOR_CURRENT);
		powerWatt = vescUart->data.avgMotorCurrent * voltage;

		// Code borrowed from
		// https://github.com/TomStanton/VESC_LCD_EBIKE/blob/master/VESC6_LCD_EBIKE.ino

		// The '42' is the number of motor poles multiplied by 3
		tachometer = (vescUart->data.tachometerAbs) / MOTOR_POLE_PAIRS * 3;
		rpm = (vescUart->data.rpm) / MOTOR_POLE_PAIRS;
		// Motor tacho x Pi x (1 / meters in a mile or km) x Wheel diameter x (motor pulley / wheelpulley)
		distance = tachometer * PI * (1.0 / 1000.0) * WHEEL_DIAMETER * (MOTOR_PULLEY / WHEEL_PULLEY);
		// Motor RPM x Pi x (seconds in a minute / meters in a kilometer) x Wheel diameter x (motor pulley /
		// wheelpulley)
		velocity = rpm * PI * WHEEL_DIAMETER * (60.0 / 1000.0) * (MOTOR_PULLEY / WHEEL_PULLEY);
		// ((Battery voltage - minimum voltage) / number of cells) x 100
		batPercentage =
			100 * (vescUart->data.inpVoltage - MIN_BATTERY_VOLTAGE) / (MAX_BATTERY_VOLTAGE - MIN_BATTERY_VOLTAGE);

		odo = origOdo + distance;
		avgSpeed = distance / (millis() / 1000.0 / 3600.0);

		if (velocity > maxSpeed) {
			maxSpeed = velocity;
			save();
		}

		mode = Live;
	}
	else {
		Serial.println("Failed to get data!");
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

void Vesc::loadInternal() {
	maxSpeed = WireBus::readFloat(12);
	odo = WireBus::readFloat(16);

	if (isnan(maxSpeed)) {
		maxSpeed = 0;
	}

	if (isnan(odo)) {
		odo = 0;
	}

	Serial.printf("loaded %f, %f", maxSpeed, odo);
	origOdo = odo;
	// save();
	// delay(20);
	loadRequested = false;
}

void Vesc::save() {
	saveRequested = true;
}

void Vesc::saveInternal() {
	Serial.printf("saving %f, %f", maxSpeed, odo);
	WireBus::writeFloat(12, maxSpeed);
	WireBus::writeFloat(16, odo);
	Serial.printf("saved %f, %f", maxSpeed, odo);
	saveRequested = false;
}
