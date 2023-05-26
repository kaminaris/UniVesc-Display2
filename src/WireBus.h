
#ifndef VESCTEST_WIREBUS_H
#define VESCTEST_WIREBUS_H

#include <Wire.h>  // must be included here so that Arduino library object file references work

#define I2C_SDA 12
#define I2C_SCL 13

#define AT24C32_I2C_ADDRESS 0x50  // the I2C address of Tiny RTC AT24C32 EEPROM
#define DS1307_I2C_ADDRESS 0x68

#define DS1307_REG_TIMEDATE_SIZE 7

#define DS1307_REG_TIMEDATE 0x00
#define DS1307_REG_STATUS 0x00
#define DS1307_REG_CONTROL 0x07
#define DS1307_REG_RAMSTART 0x08
#define DS1307_REG_RAMEND 0x3f
#define min(a, b) ((a) < (b) ? (a) : (b))

const uint8_t DS1307_REG_RAMSIZE = DS1307_REG_RAMEND - DS1307_REG_RAMSTART;

class WireBus {
	public:
	static char dateString[20];
	static char timeString[20];
	static uint16_t year;
	static uint8_t month;
	static uint8_t day;
	static uint8_t hour;
	static uint8_t minute;
	static uint8_t second;

	// int _id;
	static uint8_t _b[8];
	static uint8_t _pageSize;

	static void init();

	static void write(unsigned int address, uint8_t data);
	static void write(unsigned int address, uint8_t* data, int n);
	static void writeInt(unsigned int address, unsigned int data);
	static void writeLong(unsigned int address, unsigned long data);
	static void writeFloat(unsigned int address, float data);
	static void writeDouble(unsigned int address, double data);
	static void writeChars(unsigned int address, char* data, int length);

	static uint8_t read(unsigned int address);
	static void read(unsigned int address, uint8_t* data, int n);
	static unsigned int readInt(unsigned int address);
	static unsigned long readLong(unsigned int address);
	static float readFloat(unsigned int address);
	static double readDouble(unsigned int address);
	static void readChars(unsigned int address, char* data, int n);

	static void getTime();
	static void
	setTime(uint8_t second, uint8_t minute, uint8_t hour, uint8_t dayOfWeek, uint8_t day, uint8_t month, uint16_t year);

	protected:
	static void write(unsigned int address, uint8_t* data, int offset, int n);
	static void read(unsigned int address, uint8_t* data, int offset, int n);
};

#endif
