#include "AppSerial.h"

NimBLEServer* pServer = nullptr;
NimBLECharacteristic* pTxCharacteristic;

bool deviceConnected = false;
bool oldDeviceConnected = false;
u8_t txValue[512] = {0};
FastCRC32 CRC32;

struct BasicResponse okResponse = {(u8_t)ResponseCode::OK};
struct BasicResponse failResponse = {(u8_t)ResponseCode::FAIL};
struct BasicResponse unknownPacketResponse = {(u8_t)ResponseCode::UNKNOWN_PACKET};

void MyCallbacks::onWrite(NimBLECharacteristic* pCharacteristic) {
	auto rxValue = pCharacteristic->getValue();

	if (rxValue.length() > 0) {
		u8_t* data = (u8_t*)(rxValue.data() + 1);
		// Serial.println("*********");
		//  Serial.print("Received Value: ");
		//  for (int i = 0; i < rxValue.length(); i++) Serial.print(rxValue[i]);

		u8_t packetType = rxValue[0];
		// Serial.printf("Received packet: %d", packetType);

		switch (packetType) {
			case PacketType::PING: {
				auto* request = (PingPacket*)data;

				if (request->q == 128) {
					AppSerial::respondOk();
				}
				else {
					AppSerial::respondFail();
				}
				break;
			}

			case PacketType::GET_CLOCK: {
				struct ClockResponse clk = {
					WireBus::year,
					WireBus::month,
					WireBus::day,
					WireBus::hour,
					WireBus::minute,
					WireBus::second,
				};
				pTxCharacteristic->setValue((u8_t*)&clk, sizeof(clk));
				pTxCharacteristic->notify();
				break;
			}

			case PacketType::GET_EEPROM: {
				auto* request = (EepromReadRequest*)data;
				Serial.printf("Reading eeprom from address: %d\n", request->address);

				struct EepromPacket rsp = {};
				rsp.address = request->address;
				WireBus::read(request->address, (u8_t*)&rsp.d, 128);

				pTxCharacteristic->setValue((u8_t*)&rsp, sizeof(rsp));
				pTxCharacteristic->notify();
				break;
			}

			case PacketType::SET_EEPROM: {
				auto* request = (EepromPacket*)data;
				Serial.printf("Writing eeprom from address: %d\n", request->address);

				WireBus::write(request->address, (u8_t*)&request->d, 128);
				AppSerial::respondOk();
				break;
			}

			case PacketType::FIRMWARE_UPDATE: {
				auto* request = (FirmwareUpdateRequest*)data;

				if (request->chunk % 20 == 0) {
					Serial.printf(
						"firmware update chunk: %d/%d crc: %08X\n",
						request->chunk,
						request->chunks,
						request->checksum
					);
				}

				auto chunkCrc = CRC32.crc32(request->d, request->size);
				if (chunkCrc != request->checksum) {
					Serial.printf(
						"Chunk CRC does not match! Calculated: %08X Given: %08X \n", chunkCrc, request->checksum
					);

					Update.rollBack();
					Update.abort();
					AppSerial::respondFail();
					break;
				}

				if (request->chunk == 1) {
					if (!Update.begin(request->totalSize, U_FLASH)) {
						Serial.println("Cannot start flash update!");
						AppSerial::respondFail();
						break;
					}
					Update.write(request->d, request->size);
				}
				else if (request->chunk == request->chunks) {
					Update.write(request->d, request->size);
					if (Update.end()) {
						Serial.println("Update finished!");
						AppSerial::respondOk();
						ESP.restart();
					}
					else {
						Serial.printf("Update error: %d\n", Update.getError());
						AppSerial::respondFail();
					}
				}
				else {
					Update.write(request->d, request->size);
				}

				// do not respond
				// AppSerial::respondOk();
				break;
			}

			default: {
				AppSerial::respondUnknownPacket();
				break;
			}
		}
	}
}

void MyServerCallbacks::onConnect(NimBLEServer* pServer, ble_gap_conn_desc* desc) {
	deviceConnected = true;
	Serial.print("Client address: ");
	Serial.println(NimBLEAddress(desc->peer_ota_addr).toString().c_str());
	/** We can use the connection handle here to ask for different connection parameters.
	 *  Args: connection handle, min connection interval, max connection interval
	 *  latency, supervision timeout.
	 *  Units; Min/Max Intervals: 1.25 millisecond increments.
	 *  Latency: number of intervals allowed to skip.
	 *  Timeout: 10 millisecond increments, try for 5x interval time for best results.
	 */
	pServer->updateConnParams(desc->conn_handle, 1, 1, 0, 60);
};

void MyServerCallbacks::onMTUChange(uint16_t MTU, ble_gap_conn_desc* desc) {
	Serial.printf("MTU updated: %u for connection ID: %u\n", MTU, desc->conn_handle);
};

void MyServerCallbacks::onDisconnect(NimBLEServer* pServer) {
	deviceConnected = false;
	NimBLEDevice::startAdvertising();
}

void AppSerial::setup() {
	// Create the BLE Device
	NimBLEDevice::init("UART Service");
	NimBLEDevice::setPower(ESP_PWR_LVL_P9);
	NimBLEDevice::setMTU(512);

	// Create the BLE Server
	pServer = NimBLEDevice::createServer();
	pServer->setCallbacks(new MyServerCallbacks());

	// Create the BLE Service
	auto pService = pServer->createService(SERVICE_UUID);

	// Create a BLE Characteristic
	pTxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_TX, NIMBLE_PROPERTY::NOTIFY);

	auto pRxCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID_RX, NIMBLE_PROPERTY::WRITE_NR);

	pRxCharacteristic->setCallbacks(new MyCallbacks());

	// Start the service
	pService->start();

	// Start the server
	pServer->start();

	NimBLEAdvertising* pAdvertising = NimBLEDevice::getAdvertising();
	pAdvertising->addServiceUUID(pService->getUUID());
	/** If your device is battery powered you may consider setting scan response
	 *  to false as it will extend battery life at the expense of less data sent.
	 */
	// pAdvertising->setScanResponse(true);
	// Start advertising
	pAdvertising->start();

	Serial.println("Waiting a client connection to notify...");

	// xTaskCreatePinnedToCore(AppSerial::loop, "AppSerial::loop", 8192, nullptr, 6, nullptr, ARDUINO_RUNNING_CORE);
}

[[noreturn]] void AppSerial::loop(void* p) {
	while (true) {
		// disconnecting
		if (!deviceConnected && oldDeviceConnected) {
			delay(500);									 // give the bluetooth stack the chance to get things ready
			bool success = pServer->startAdvertising();	 // restart advertising
			Serial.print("start advertising: ");
			Serial.println(success ? "true" : "false");
			oldDeviceConnected = deviceConnected;
		}

		// connecting
		if (deviceConnected && !oldDeviceConnected) {
			// do stuff here on connecting
			oldDeviceConnected = deviceConnected;
		}

		delay(10);
	}
}

void AppSerial::respondOk() {
	pTxCharacteristic->setValue((u8_t*)&okResponse, sizeof(okResponse));
	pTxCharacteristic->notify();
}

void AppSerial::respondFail() {
	pTxCharacteristic->setValue((u8_t*)&failResponse, sizeof(failResponse));
	pTxCharacteristic->notify();
}

void AppSerial::respondUnknownPacket() {
	pTxCharacteristic->setValue((u8_t*)&unknownPacketResponse, sizeof(unknownPacketResponse));
	pTxCharacteristic->notify();
}
