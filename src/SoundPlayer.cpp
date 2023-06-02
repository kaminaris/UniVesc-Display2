#include "SoundPlayer.h"

bool SoundPlayer::playing = false;
Audio* SoundPlayer::audio = nullptr;
QueueHandle_t SoundPlayer::audioSetQueue = nullptr;

void SoundPlayer::init() {
	audio = new Audio();
	audio->setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
	audio->setVolume(5);  // 0...21
	audio->forceMono(true);
	playing = false;
	audioSetQueue = xQueueCreate(10, sizeof(struct AudioMessage));

	xTaskCreatePinnedToCore(SoundPlayer::loop, "Music Player", 16384, nullptr, 1, nullptr, 1);
}

void SoundPlayer::setVolume(u8_t volume) {
	// audio->setVolume(volume);  // 0...21
	struct AudioMessage msg = {
		.cmd = (u8_t)SoundPlayer::SET_VOLUME,
		.value = volume,
	};
	xQueueSend(audioSetQueue, &msg, portMAX_DELAY);
}

void SoundPlayer::play(const char* path) {
	struct AudioMessage msg = {
		.cmd = (u8_t)SoundPlayer::PLAY,
		.txt = path,
	};
	xQueueSend(audioSetQueue, &msg, portMAX_DELAY);
}

[[noreturn]] void SoundPlayer::loop(__unused void* parameter) {
	struct AudioMessage audioRxTaskMessage = {};

	while (true) {
		if (xQueueReceive(audioSetQueue, &audioRxTaskMessage, 1) == pdPASS) {
			if (audioRxTaskMessage.cmd == SoundPlayer::SET_VOLUME) {
				audio->setVolume(audioRxTaskMessage.value);
			}
			else if (audioRxTaskMessage.cmd == SoundPlayer::PLAY) {
				audio->connecttoFS(SPIFFS, audioRxTaskMessage.txt);
			}
		}

		audio->loop();

		if (!audio->isRunning()) {
			sleep(1);
		}
	}
}

void SoundPlayer::playPause() {
	audio->pauseResume();
}