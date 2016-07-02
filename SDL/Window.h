#ifndef CITY_WINDOW_H
#define CITY_WINDOW_H

#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

#include "SDL.h"
#include "Texture.h"

class SDL::Window {

    SDL_Window *window = NULL;

    SDL_Renderer *renderer;

public:

    ~Window();

    Window(int width, int height);

    bool valid();

    SDL_Renderer * getRenderer();

    void update();

    void setTitle(const char string[7]);


};


#endif //CITY_WINDOW_H
