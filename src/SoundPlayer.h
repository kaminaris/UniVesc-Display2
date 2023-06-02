#ifndef UNIVESCDISPLAY2_SOUNDPLAYER_H
#define UNIVESCDISPLAY2_SOUNDPLAYER_H

#include "Audio.h"
#include "SPIFFS.h"

#define I2S_DOUT 37
#define I2S_BCLK 36
#define I2S_LRC 35



struct AudioMessage {
	u8_t cmd;
	const char* txt;
	u32_t value;
	u32_t ret;
};

class SoundPlayer {
	enum : u8_t { SET_VOLUME, GET_VOLUME, PLAY };
	public:
	static QueueHandle_t audioSetQueue;
	static bool playing;
	static Audio* audio;

	static void init();
	[[noreturn]] static void loop(void* parameter);
	static void playPause();
	static void play(const char* path);
	static void setVolume(u8_t volume);
};

#endif
