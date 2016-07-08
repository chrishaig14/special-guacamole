/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL and standard IO
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <map>
#include "SDL/SDL.h"
#include "SDL/Texture.h"
#include "SDL/Window.h"
#include "SDL/SDL_Resources.h"
#include "SDL/Text.h"
#include "SDL/Price.h"
#include "SDL/Cell.h"
#include "SDL/GameGrid.h"

//Screen dimension constants
#include "SDL/screen.h"

Uint32 callback( Uint32 interval, void* param ){
    std::cout << interval << " passed" << std::endl;
}

void drawGrid(SDL::Renderer* renderer, int g){
    for (int i = 0; i < SCREEN_WIDTH/g; ++i) {
        renderer->drawLine(i*g,0,i*g,SCREEN_HEIGHT);
    }
    for (int i = 0; i < SCREEN_HEIGHT/g; ++i) {
        renderer->drawLine(0,i*g,SCREEN_WIDTH,i*g);
    }
}


int main(int argc, char *args[]) {
    SDL::init();
    SDL::Window window (SCREEN_WIDTH,SCREEN_HEIGHT);
    SDL::Renderer* renderer = window.getRenderer();
    SDL_Resources resources(renderer);
    resources.addTexture("cellAlive", "images/red.png");
    resources.addTexture("cellDead", "images/white.png");

    resources.addTexture("cursor","images/cursor.png");
    SDL::Texture* cursor = resources.getTexture("cursor");
    SDL::Texture* cellTextureAlive = resources.getTexture("cellAlive");
    SDL::Texture* cellTextureDead = resources.getTexture("cellDead");
    SDL_ShowCursor(0);


    bool quit = false;
    SDL_Event e;
    int x,y;



    int frames = 0;
    Cell cell (cellTextureAlive, cellTextureDead);
    //std::cout << "OK 1" << std::endl;
    GameGrid grid (GRID,GRID,cell);
    //std::cout << "OK 1" << std::endl;
    int initTime = SDL::getTicks();
    std::string fpsStr;
    std::string mouseStr;
    std::string tileStr;
    int timeSinceLastUpdate = SDL::getTicks();
   // std::cout << "OK 1" << std::endl;
    bool debug = false;
    while(!quit) {
        int t0 = SDL::getTicks();
        while(SDL_PollEvent(&e)){
            if(e.type == SDL_KEYDOWN){
                if(e.key.keysym.sym == SDLK_ESCAPE){
                    quit = true;
                }
                else if(e.key.keysym.sym == SDLK_F11){
                    window.toggleFullScreen();
                    frames = 0;
                    initTime = SDL::getTicks();
                }
                else if(e.key.keysym.sym == SDLK_F5){
                    debug = !debug;
                }
            }
            if(e.type == SDL_MOUSEBUTTONDOWN){

                SDL::getMouseState(&x,&y);
                int i = y / (SCREEN_HEIGHT / GRID);
                int j = x / (SCREEN_WIDTH / GRID);
                grid.setTile(i,j);
            }
            if(e.type == SDL_MOUSEMOTION){
                SDL::getMouseState(&x,&y);
                mouseStr = std::to_string(x);
                mouseStr += " , ";
                mouseStr += std::to_string(y);
            }
        }
        renderer -> setColor(255,255,255,255);
        renderer -> clear();


        if(!debug) {
            if (SDL::getTicks() - timeSinceLastUpdate > 50) {
                grid.update();
                timeSinceLastUpdate = SDL::getTicks();
                std::cout << "Updated at time: " << timeSinceLastUpdate << std::endl;
            }
        }
        //std::cout << "OK 1" << std::endl;
        grid.draw();
        //std::cout << "OK 1" << std::endl;

        renderer -> setColor(0,0,0,255);
        drawGrid(renderer, GRID);

        int j = 0;

        SDL::getMouseState(&x,&y);
        cursor ->render(x,y,32,32);
        frames++;
        int t1 = SDL::getTicks();
        float fps = (float)frames / ((float)(t1 - initTime) / 1000);
        fpsStr = std::to_string(fps);
        SDL::Text debugText (renderer,fpsStr + "\n" + mouseStr,"Montserrat-Regular.ttf",10,0,255,0);
        debugText.render(0,0);
        renderer->present();
        if(t1 - t0 < 1000/30){
            SDL::delay(1000/30 - (t1-t0));
        }
    }
    SDL::quit();
}
