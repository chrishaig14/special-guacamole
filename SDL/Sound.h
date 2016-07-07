//
// Created by chris on 03/07/16.
//

#ifndef CITY_SOUND_H
#define CITY_SOUND_H


#include <SDL2/SDL_mixer.h>
#include "SDL.h"
#include <string>

class SDL::Sound {
    Mix_Chunk* sound;
public:
    Sound(std::string filename);

    void play();

    ~Sound();
};


#endif //CITY_SOUND_H
