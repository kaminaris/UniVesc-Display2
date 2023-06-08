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

	// higher than lvgl
	xTaskCreatePinnedToCore(SoundPlayer::loop, "Music Player", 16384, nullptr, 10, nullptr, 1);
}

void SoundPlayer::setVolume(u8_t volume) {
	struct AudioMessage msg = {
		.cmd = (u8_t)SoundPlayer::SET_VOLUME,
		.value = volume,
	};
	xQueueSend(audioSetQueue, &msg, portMAX_DELAY);
}

void SoundPlayer::play(const char* path) {
	struct AudioMessage msg = {
		.cmd = (u8_t)SoundPlayer::PLAY,
	};
	strcpy(msg.fileName, path);
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
				bool result = audio->connecttoFS(SPIFFS, audioRxTaskMessage.fileName);
				appSerial.printf("Playing File: %s %d\n", audioRxTaskMessage.fileName, (int)result);
			}
		}

		audio->loop();

		if (!audio->isRunning()) {
			vTaskDelay(pdMS_TO_TICKS(100));
		}
	}
}

void SoundPlayer::playPause() {
	audio->pauseResume();
}