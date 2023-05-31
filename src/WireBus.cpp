#include "WireBus.h"

// EEPROM Code borrowed from https://github.com/cyberp/AT24Cx

u8_t BcdToUint8(u8_t val) {
	return val - 6 * (val >> 4);
}

u8_t Uint8ToBcd(u8_t val) {
	return val + 6 * (val / 10);
}

u8_t BcdToBin24Hour(u8_t bcdHour) {
	u8_t hour;
	if (bcdHour & 0x40) {
		// 12 hour mode, convert to 24
		bool isPm = ((bcdHour & 0x20) != 0);

		hour = BcdToUint8(bcdHour & 0x1f);
		if (isPm) {
			hour += 12;
		}
	}
	else {
		hour = BcdToUint8(bcdHour);
	}
	return hour;
}

char WireBus::dateString[20] = {0};
char WireBus::timeString[20] = {0};
uint16_t WireBus::year = 0;
u8_t WireBus::month = 0;
u8_t WireBus::day = 0;
u8_t WireBus::hour = 0;
u8_t WireBus::minute = 0;
u8_t WireBus::second = 0;
u8_t WireBus::_b[8] = {0};
u8_t WireBus::_pageSize = 32;

void WireBus::init() {
	Wire1.begin(I2C_SDA, I2C_SCL);	// 17, 16
}
// AT24C32_I2C_ADDRESS

/**
 * Write u8_t
 */
void WireBus::write(unsigned int address, u8_t data) {
	Wire1.beginTransmission(AT24C32_I2C_ADDRESS);
	if (Wire1.endTransmission() == 0) {
		Wire1.beginTransmission(AT24C32_I2C_ADDRESS);
		Wire1.write(address >> 8);
		Wire1.write(address & 0xFF);
		Wire1.write(data);
		Wire1.endTransmission();
		delay(20);
	}
}

/**
 * Write sequence of n bytes
 */
void WireBus::write(unsigned int address, u8_t* data, int n) {
	// status quo
	int c = n;	   // bytes left to write
	int offD = 0;  // current offset in data pointer
	int offP;	   // current offset in page
	int nc = 0;	   // next n bytes to write

	// write alle bytes in multiple steps
	while (c > 0) {
		// calc offset in page
		offP = address % _pageSize;
		// maximal 30 bytes to write
		nc = min(min(c, 30), _pageSize - offP);
		write(address, data, offD, nc);
		c -= nc;
		offD += nc;
		address += nc;
	}
}

/**
 * Write sequence of n bytes from offset
 */
void WireBus::write(unsigned int address, u8_t* data, int offset, int n) {
	Wire1.beginTransmission(AT24C32_I2C_ADDRESS);
	if (Wire1.endTransmission() == 0) {
		Wire1.beginTransmission(AT24C32_I2C_ADDRESS);
		Wire1.write(address >> 8);
		Wire1.write(address & 0xFF);
		u8_t* adr = data + offset;
		Wire1.write(adr, n);
		Wire1.endTransmission();
		delay(20);
	}
}

/**
 * Read u8_t
 */
u8_t WireBus::read(unsigned int address) {
	u8_t b = 0;
	int r = 0;
	Wire1.beginTransmission(AT24C32_I2C_ADDRESS);
	if (Wire1.endTransmission() == 0) {
		Wire1.beginTransmission(AT24C32_I2C_ADDRESS);
		Wire1.write(address >> 8);
		Wire1.write(address & 0xFF);
		if (Wire1.endTransmission() == 0) {
			Wire1.requestFrom(AT24C32_I2C_ADDRESS, 1);
			while (Wire1.available() > 0 && r < 1) {
				b = (u8_t)Wire1.read();
				r++;
			}
		}
	}
	return b;
}

/**
 * Read sequence of n bytes
 */
void WireBus::read(unsigned int address, u8_t* data, int n) {
	int c = n;
	int offD = 0;
	// read until are n bytes read
	while (c > 0) {
		// read maximal 32 bytes
		int nc = c;
		if (nc > 32) nc = 32;
		read(address, data, offD, nc);
		address += nc;
		offD += nc;
		c -= nc;
	}
}

/**
 * Read sequence of n bytes to offset
 */
void WireBus::read(unsigned int address, u8_t* data, int offset, int n) {
	Wire1.beginTransmission(AT24C32_I2C_ADDRESS);
	if (Wire1.endTransmission() == 0) {
		Wire1.beginTransmission(AT24C32_I2C_ADDRESS);
		Wire1.write(address >> 8);
		Wire1.write(address & 0xFF);
		if (Wire1.endTransmission() == 0) {
			int r = 0;
			Wire1.requestFrom(AT24C32_I2C_ADDRESS, n);
			while (Wire1.available() > 0 && r < n) {
				data[offset + r] = (u8_t)Wire1.read();
				r++;
			}
		}
	}
}

/**
 * Write integer
 */
void WireBus::writeInt(unsigned int address, unsigned int data) {
	write(address, (u8_t*)&data, 2);
}

/**
 * Write long
 */
void WireBus::writeLong(unsigned int address, unsigned long data) {
	write(address, (u8_t*)&data, 4);
}

/**
 * Write float
 */
void WireBus::writeFloat(unsigned int address, float data) {
	write(address, (u8_t*)&data, 4);
}

/**
 * Write double
 */
void WireBus::writeDouble(unsigned int address, double data) {
	write(address, (u8_t*)&data, 8);
}

/**
 * Write chars
 */
void WireBus::writeChars(unsigned int address, char* data, int length) {
	write(address, (u8_t*)data, length);
}

/**
 * Read integer
 */
unsigned int WireBus::readInt(unsigned int address) {
	read(address, _b, 2);
	return *(unsigned int*)&_b[0];
}

/**
 * Read long
 */
unsigned long WireBus::readLong(unsigned int address) {
	read(address, _b, 4);
	return *(unsigned long*)&_b[0];
}

/**
 * Read float
 */
float WireBus::readFloat(unsigned int address) {
	read(address, _b, 4);
	return *(float*)&_b[0];
}

/**
 * Read double
 */
double WireBus::readDouble(unsigned int address) {
	read(address, _b, 8);
	return *(double*)&_b[0];
}

/**
 * Read chars
 */
void WireBus::readChars(unsigned int address, char* data, int n) {
	read(address, (u8_t*)data, n);
}

void WireBus::getTime() {
	Wire1.beginTransmission(DS1307_I2C_ADDRESS);
	Wire1.write(DS1307_REG_TIMEDATE);
	u8_t _lastError = Wire1.endTransmission();
	if (_lastError != 0) {
		// Serial.println("fail");
		// Serial.println(_lastError);
	}

	u8_t bytesRead = Wire1.requestFrom(DS1307_I2C_ADDRESS, DS1307_REG_TIMEDATE_SIZE);

	second = BcdToUint8(Wire1.read() & 0x7F);
	minute = BcdToUint8(Wire1.read());
	hour = BcdToBin24Hour(Wire1.read());

	Wire1.read();  // throwing away day of week as we calculate it

	day = BcdToUint8(Wire1.read());
	month = BcdToUint8(Wire1.read());
	year = BcdToUint8(Wire1.read()) + 2000;

	snprintf(
		timeString,
		sizeof(timeString),
		PSTR("%02u:%02u:%02u"),	 // %02u/%02u/%04u
		hour,
		minute,
		second
	);

	snprintf(
		dateString,
		sizeof(dateString),
		PSTR("%04u-%02u-%02u"),	 // %02u/%02u/%04u
		year,
		month,
		day
	);
}

void WireBus::setTime(
	u8_t second,
	u8_t minute,
	u8_t hour,
	u8_t dayOfWeek,
	u8_t day,
	u8_t month,
	uint16_t year
) {
	// u8_t sreg = getReg(DS1307_REG_STATUS) & _BV(DS1307_CH);

	// set the date time
	Wire1.beginTransmission(DS1307_I2C_ADDRESS);
	Wire1.write(DS1307_REG_TIMEDATE);

	Wire1.write(Uint8ToBcd(second));  // | sreg
	Wire1.write(Uint8ToBcd(minute));
	Wire1.write(Uint8ToBcd(hour));	// 24 hour mode only

	Wire1.write(Uint8ToBcd(dayOfWeek));
	Wire1.write(Uint8ToBcd(day));
	Wire1.write(Uint8ToBcd(month));
	Wire1.write(Uint8ToBcd(year - 2000));

	u8_t _lastError = Wire1.endTransmission();
	if (_lastError != 0) {
		// Serial.println("fail");
	}

	WireBus::year = year;
	WireBus::month = month;
	WireBus::day = day;
	WireBus::hour = hour;
	WireBus::minute = minute;
	WireBus::second = second;
}