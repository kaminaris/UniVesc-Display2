#ifndef UNIVESCDISPLAY2_PACKETS_H
#define UNIVESCDISPLAY2_PACKETS_H

#include <Arduino.h>

#define Packed __attribute__((packed))

enum class ResponseCode : u8_t {
	OK = 7,
	FAIL,
	UNKNOWN_PACKET
};

enum PacketType {
	PING = 1,
	GET_CLOCK,
	GET_EEPROM,
	SET_EEPROM,
	FIRMWARE_UPDATE
};

struct Packed PingPacket {
	u8_t q;
};

struct Packed BasicResponse {
	u8_t r;
};

struct Packed ClockResponse {
	u16_t year;
	u8_t month;
	u8_t day;
	u8_t hour;
	u8_t minute;
	u8_t second;
};

// both read and write
struct Packed EepromReadRequest {
	u16_t address;
};

struct Packed FirmwareUpdateRequest {
	u32_t chunk;
	u32_t chunks;
	u16_t size;
	u32_t totalSize;
	u32_t checksum;
	u8_t d[450];
};

struct Packed EepromPacket {
	u16_t address;
	u8_t d[128];
};

#endif