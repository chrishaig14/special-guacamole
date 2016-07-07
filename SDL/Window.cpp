//
// Created by chris on 26/06/16.
//

#include "Window.h"

SDL::Window::Window(int width, int height) {
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if(window) {
//        SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
//        SDL_Renderer* renderer_ptr = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
        SDL_Renderer* renderer_ptr = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
        renderer = new Renderer(renderer_ptr);
        renderer->setColor(0xff,0xff,0xff,0xff);
    }
}

bool SDL::Window::valid(){
    return window != NULL;
}

void SDL::Window::toggleFullScreen(){
    if((SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN) == SDL_WINDOW_FULLSCREEN) {
        SDL_SetWindowFullscreen(window, 0);
    } else {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }
}

SDL::Window::~Window() {
    if (window) {
        SDL_DestroyWindow(window);
        delete renderer;

    }
}

SDL::Renderer * SDL::Window::getRenderer() {
    return renderer;
}

void SDL::Window::update() {
    SDL_UpdateWindowSurface(window);
}

void SDL::Window::setTitle(const char *string) {
    SDL_SetWindowTitle(window,string);
}



