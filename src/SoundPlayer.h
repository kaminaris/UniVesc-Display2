#ifndef UNIVESCDISPLAY2_SOUNDPLAYER_H
#define UNIVESCDISPLAY2_SOUNDPLAYER_H

#include "Audio.h"
#include "SPIFFS.h"

#define I2S_DOUT 37
#define I2S_BCLK 36
#define I2S_LRC 35

class SoundPlayer {
	public:
	static bool playing;
	static Audio* audio;

	static void init();
	static void loop(void* parameter);
	static void playPause();
	static void play(const char* path);
};

#endif
