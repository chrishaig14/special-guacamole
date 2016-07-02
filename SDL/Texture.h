#ifndef CITY_SURFACE_H
#define CITY_SURFACE_H

#include <string>
#include "SDL.h"

class SDL::Texture {

    SDL_Texture *texture;

public:

    Texture();

    void loadImage(SDL_Renderer* renderer, const std::string &filename);

    bool valid();

    ~Texture();

    void optimize(SDL::Texture *screenSurface);

    SDL_Texture *getTexture();
};


#endif //CITY_SURFACE_H
