//
// Created by chris on 03/07/16.
//

#include "Music.h"

SDL::Music::Music(std::string filename) {
    music = NULL;
    music = Mix_LoadMUS(filename.c_str());
}

void SDL::Music::play() {
    Mix_PlayMusic(music, -1);

}

SDL::Music::~Music() {
    Mix_FreeMusic(music);
}