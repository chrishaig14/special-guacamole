//
// Created by chris on 03/07/16.
//

#include "Renderer.h"

SDL::Renderer::Renderer(SDL_Renderer* renderer) {
    this -> renderer = renderer;
}

void SDL::Renderer::setColor(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(renderer,r,g,b,a);
}

void SDL::Renderer::fillRect(SDL_Rect* rect) {
    SDL_RenderFillRect(renderer,rect);
}

void SDL::Renderer::drawRect(SDL_Rect* rect) {
    SDL_RenderDrawRect(renderer,rect);
}

void SDL::Renderer::drawLine(int x0, int y0, int x1, int y1) {
    SDL_RenderDrawLine(renderer,x0,y0,x1,y1);
}

void SDL::Renderer::drawPoint(int x, int y) {
    SDL_RenderDrawPoint(renderer,x,y);
}

void SDL::Renderer::render(SDL::Texture* texture, SDL_Rect* rect1, SDL_Rect* rect2) {
    SDL_RenderCopy( renderer, texture -> getTexture(), rect1, rect2);
}

SDL::Renderer::~Renderer() {
    SDL_DestroyRenderer( renderer );
}

SDL_Renderer *SDL::Renderer::getRenderer() {
    return renderer;
}

void SDL::Renderer::present() {
    SDL_RenderPresent(renderer);
}

void SDL::Renderer::clear() {
    SDL_RenderClear( renderer );
}