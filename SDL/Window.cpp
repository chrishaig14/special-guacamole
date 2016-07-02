//
// Created by chris on 26/06/16.
//

#include "Window.h"

SDL::Window::Window(int width, int height) {
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if(window) {
//        SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
//        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

    }
}

bool SDL::Window::valid(){
    return window != NULL;
}

SDL::Window::~Window() {
    if (window) {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer( renderer );
    }
}

SDL_Renderer *SDL::Window::getRenderer() {
    return renderer;
}

void SDL::Window::update() {
    SDL_UpdateWindowSurface(window);
}

void SDL::Window::setTitle(const char *string) {
    SDL_SetWindowTitle(window,string);
}



