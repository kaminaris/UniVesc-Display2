#ifndef UNIVESCDISPLAY2_APPSERIAL_H
#define UNIVESCDISPLAY2_APPSERIAL_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include <NimBLEAdvertising.h>
#include <NimBLEDevice.h>
#include <NimBLEServer.h>
#include <NimBLEUtils.h>
#include <Update.h>
#include <FastCRC.h>

#include <cstring>

#include "WireBus.h"
#include "packets.h"

#define SERVICE_UUID "9C12D201-CBC3-413B-963B-9E49FF7E7D31"
#define CHARACTERISTIC_UUID_TX "9C12D202-CBC3-413B-963B-9E49FF7E7D31"
#define CHARACTERISTIC_UUID_RX "9C12D203-CBC3-413B-963B-9E49FF7E7D31"

class MyServerCallbacks : public NimBLEServerCallbacks {
	void onDisconnect(NimBLEServer* pServer) override;

	void onConnect(NimBLEServer* pServer, ble_gap_conn_desc* desc) override;

	void onMTUChange(uint16_t MTU, ble_gap_conn_desc* desc) override;
};

class MyCallbacks : public NimBLECharacteristicCallbacks {
	void onWrite(NimBLECharacteristic* pCharacteristic) override;
};

class AppSerial {
	public:
	static void setup();
	[[noreturn]] static void loop(void* p);
	static void respondOk();
	static void respondFail();
	static void respondUnknownPacket();
};

#endif
