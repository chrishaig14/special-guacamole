#ifndef CITY_SDL_H
#define CITY_SDL_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

namespace SDL {

    int init();

    void delay(int ms);

    int getTicks();

    int getMouseState(int*x, int* y);

    class Window;

    class Renderer;

    class Texture;

    class Text;

    class Sound;

    class Music;

    void quit();
};


#endif //CITY_SDL_H
