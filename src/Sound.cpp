#define MINIAUDIO_IMPLEMENTATION
#include "Sound.h"

SoundCore::SoundCore() {
    statusSoundCore = ma_engine_init(NULL, &engineSoundCore);
    if (statusSoundCore != MA_SUCCESS) {
        infoLog = "MINIAUDIO::ENGINE_INITIALIZATION::FAILED\n";
    }
}

SoundCore::~SoundCore() {
    ma_engine_uninit(&engineSoundCore);
}

void SoundCore::SCPlaySound(const char* audio_path) {
    ma_engine_play_sound(&engineSoundCore, audio_path, NULL);
}