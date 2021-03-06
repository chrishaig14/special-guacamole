#include <iostream>
#include "SDL.h"

int ::SDL::init() {
    int r = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_TIMER);
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        std::cout << "Error!" << std::endl;
    }
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
    }
    TTF_Init();
    return r;
}

void ::SDL::delay(int ms) {
    SDL_Delay( ms );
}

int ::SDL::getTicks() {
    return SDL_GetTicks();
}

int ::SDL::getMouseState(int*x, int* y) {
    return SDL_GetMouseState(x,y);
}

void ::SDL::quit() {
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}