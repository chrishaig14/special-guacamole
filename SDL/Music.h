//
// Created by chris on 03/07/16.
//

#ifndef CITY_MUSIC_H
#define CITY_MUSIC_H

#include "SDL.h"
#include <SDL2/SDL_mixer.h>
#include <string>

class SDL::Music {
    Mix_Music *music;

public:
    Music(std::string filename);

    void play();

    ~Music();
};


#endif //CITY_MUSIC_H
