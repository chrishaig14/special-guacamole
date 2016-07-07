//
// Created by chris on 03/07/16.
//

#ifndef CITY_RENDERER_H
#define CITY_RENDERER_H


#include "SDL.h"
#include "Texture.h"
#include <SDL2/SDL_system.h>

class SDL::Renderer {

    SDL_Renderer* renderer;
public:
    Renderer(SDL_Renderer* renderer);

    void setColor(int r, int g, int b, int a);

    void fillRect(SDL_Rect* rect);

    void drawRect(SDL_Rect* rect);

    void drawLine(int x0, int y0, int x1, int y1);

    void drawPoint(int x, int y);

    void render(SDL::Texture* texture, SDL_Rect* rect1, SDL_Rect* rect2);

    ~Renderer();

    SDL_Renderer * getRenderer();

    void present();

    void clear();

};


#endif //CITY_RENDERER_H
