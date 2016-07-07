//
// Created by chris on 03/07/16.
//

#ifndef CITY_TEXT_H
#define CITY_TEXT_H


#include <SDL2/SDL_ttf.h>
#include "SDL.h"
#include "Renderer.h"
#include "Texture.h"
#include <string>

class SDL::Text : public SDL::Texture {

    public:

    Text(SDL::Renderer* renderer, std::string text, std::string font, int size, int r, int g, int b);

    ~Text();
};


#endif //CITY_TEXT_H
