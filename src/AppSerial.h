#ifndef UNIVESCDISPLAY2_APPSERIAL_H
#define UNIVESCDISPLAY2_APPSERIAL_H

#include <Arduino.h>
#include <FastCRC.h>
#include <NimBLEAdvertising.h>
#include <NimBLEDevice.h>
#include <NimBLEServer.h>
#include <NimBLEUtils.h>
#include <Update.h>

#include <cstring>

#include "SPIFFS.h"
#include "Sound/SoundTune.h"
#include "Sound/SoundPlayer.h"
#include "Vesc/Vesc.h"
#include "WireBus.h"
#include "packets.h"

#define SERVICE_UUID "9C12D201-CBC3-413B-963B-9E49FF7E7D31"
#define CHARACTERISTIC_UUID_TX "9C12D202-CBC3-413B-963B-9E49FF7E7D31"
#define CHARACTERISTIC_UUID_RX "9C12D203-CBC3-413B-963B-9E49FF7E7D31"
#define CHARACTERISTIC_UUID_DEBUG "9C12D204-CBC3-413B-963B-9E49FF7E7D31"

#define DUAL_SERIAL

class MyServerCallbacks : public NimBLEServerCallbacks {
	void onDisconnect(NimBLEServer* pServer) override;

	void onConnect(NimBLEServer* pServer, ble_gap_conn_desc* desc) override;

	void onMTUChange(uint16_t MTU, ble_gap_conn_desc* desc) override;
};

class MyCallbacks : public NimBLECharacteristicCallbacks {
	void onWrite(NimBLECharacteristic* pCharacteristic) override;
};

class AppSerial : public Print {
	public:
	size_t write(uint8_t) override;
	size_t write(const uint8_t* buffer, size_t size) override;
	static void setup();
	static void respondOk();
	static void respondFail();
	static void respondUnknownPacket();
};

extern AppSerial appSerial;

#endif
