#include "SoundPlayer.h"

bool SoundPlayer::playing = false;
Audio* SoundPlayer::audio = nullptr;

void SoundPlayer::init() {
	audio = new Audio();
	audio->setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
	// audio->m_pin_config = {};
	// audio->m_pin_config.bck_io_num = BCLK;
	// audio->m_pin_config.ws_io_num = LRC;  //  wclk
	// audio->m_pin_config.data_out_num = DOUT;
	// audio->m_pin_config.data_in_num = -1;
	//
	// const esp_err_t result = i2s_set_pin((i2s_port_t)m_i2s_num, &m_pin_config);
	// return (result == ESP_OK);

	audio->setVolume(5);  // 0...21
	audio->forceMono(true);
	playing = false;
}

void SoundPlayer::play(const char* path) {
	audio->connecttoFS(SPIFFS, path);

	if (!playing) {
		playing = true;
		xTaskCreatePinnedToCore(SoundPlayer::loop, "Music Player", 16384, nullptr, 1, nullptr, 1);
	}
}

void SoundPlayer::loop(void* parameter) {
	while (playing) {
		audio->loop();

		// uint32_t act = audio.getAudioCurrentTime();
		// uint32_t afd = audio.getAudioFileDuration();
	}

	vTaskDelete(nullptr);
}

void SoundPlayer::playPause() {
	audio->pauseResume();
	bool isPlay = audio->isRunning();
}