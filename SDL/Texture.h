#ifndef CITY_SURFACE_H
#define CITY_SURFACE_H

#include <string>
#include "SDL.h"
#include "Renderer.h"

class SDL::Texture {

protected:
    SDL_Texture *texture;
    SDL::Renderer* renderer;
    int w, h, a;

public:

    Texture();

    Texture(SDL::Renderer* renderer, const std::string &filename);

    bool valid();

    ~Texture();

    void optimize(SDL::Texture *screenSurface);

    SDL_Texture *getTexture();

    void render(int x, int y, int w, int h);

    void getDimensions(int* w, int *h);

    void setAlpha(int a);

    void render(int x, int y);

    int getAlpha();
};


#endif //CITY_SURFACE_H
