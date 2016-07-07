//
// Created by chris on 03/07/16.
//

#include "Sound.h"

SDL::Sound::Sound(std::string filename) {
    sound = NULL;
    sound = Mix_LoadWAV( filename.c_str());
}

void SDL::Sound::play() {
    Mix_PlayChannel(-1, sound, 0);
}

SDL::Sound::~Sound() {
    Mix_FreeChunk(sound);
}