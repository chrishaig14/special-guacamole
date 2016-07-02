#include <iostream>
#include "Texture.h"

void SDL::Texture::loadImage(SDL_Renderer* renderer, const std::string &filename) {

    SDL_Surface* surface = IMG_Load( filename.c_str() );

    if( surface == NULL ){
        std::cout << "Error loading image: " << filename << std::endl;
        return;
    }
    SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0xFF, 0xFF, 0xFF ) );
    texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_FreeSurface(surface);
}

SDL::Texture::~Texture() {
    if (texture != NULL) {
        SDL_DestroyTexture( texture );
    }
}

bool SDL::Texture::valid() {
    return texture != NULL;
}

void SDL::Texture::optimize(SDL::Texture* screenSurface){
   /* SDL_Surface* optimizedSurface = optimizedSurface = SDL_ConvertSurface( surface, screenSurface->surface->format, 0 );
    if(optimizedSurface != NULL) {
        std::cout << "OK" << std::endl;
        SDL_FreeSurface(surface);
        surface = optimizedSurface;
    }
    */
}

SDL::Texture::Texture() {
    texture = NULL;
}

SDL_Texture *SDL::Texture::getTexture() {
    return texture;
}



