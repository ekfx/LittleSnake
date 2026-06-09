#ifndef SOUND_H
#define SOUND_H

#include <string>
#include "../include/miniaudio/miniaudio.h"

class SoundCore {       // A ESTUDAR MELHOR
private:
    ma_result statusSoundCore;
    ma_engine engineSoundCore;
    std::string infoLog;

public:
    // construtor e destrutor
    SoundCore();
    ~SoundCore();

    // Utilitarios
    void SCPlaySound(const char* audio_path); // tocar som simples

};

#endif // SOUND_H