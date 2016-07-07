#include <iostream>
#include "Texture.h"
#include "Renderer.h"

SDL::Texture::Texture(){
    texture = NULL;
    renderer = NULL;
}

SDL::Texture::Texture(SDL::Renderer* renderer, const std::string &filename) {
    texture = NULL;
    this -> renderer = renderer;
    SDL_Surface* surface = IMG_Load( filename.c_str() );

    //   // SDL_SetTextureColorMod( image -> getTexture(), 23, 129, 244 );
//    //SDL_SetTextureBlendMode( image -> getTexture(), SDL_BLENDMODE_BLEND);

    if( surface == NULL ){
        std::cout << "Error loading image: " << filename << std::endl;
        return;
    }
    SDL_SetColorKey( surface, SDL_TRUE, SDL_MapRGB( surface->format, 0xff, 0xff, 0xff ) );
    SDL_Surface* optimizedSurface = SDL_ConvertSurface( surface, surface->format, 0 );
    texture = SDL_CreateTextureFromSurface(renderer->getRenderer(), optimizedSurface);
    SDL_FreeSurface(optimizedSurface);
    SDL_FreeSurface(surface);
    a = 255;
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

SDL_Texture *SDL::Texture::getTexture() {
    return texture;
}


void SDL::Texture::render(int x, int y, int w, int h) {
    //std::cout << "complete: " << a << std::endl;
    SDL_Rect rect = {x,y,w,h};
    SDL_RenderCopy(renderer -> getRenderer(), texture, NULL, &rect);
}

void SDL::Texture::render(int x, int y) {
    int w, h;
    SDL_QueryTexture(texture,NULL,NULL,&w,&h);
    render(x,y,w,h);
}

void SDL::Texture::getDimensions(int* w, int *h) {
    SDL_QueryTexture(texture,NULL,NULL,w,h);
}

int SDL::Texture::getAlpha() {
    //    //SDL_SetTextureBlendMode( image -> getTexture(), SDL_BLENDMODE_BLEND);
    return a;
}
void SDL::Texture::setAlpha(int a) {
    //    //SDL_SetTextureBlendMode( image -> getTexture(), SDL_BLENDMODE_BLEND);
    this -> a = a;
    SDL_SetTextureAlphaMod(texture,a);
}

