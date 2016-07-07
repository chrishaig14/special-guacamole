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
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int LEVEL_WIDTH = 1024;
const int LEVEL_HEIGHT = 768;

const int SPRITE_BALL = 0;
const int SPRITE_HOUSE = 1;
const int SPRITE_CAR = 2;

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
    SDL::Window window (640,480);
    SDL::Renderer* renderer = window.getRenderer();
    SDL_Resources resources(renderer);
    resources.addTexture("cell", "images/balloon.jpg");
    bool quit = false;
    SDL_Event e;
    int x,y;
    resources.addTexture("cursor","images/cursor.png");
    SDL_ShowCursor(0);
    SDL::Texture* cursor = resources.getTexture("cursor");
    int frames = 0;
    std::vector<Price*> prices;
    SDL::Text* price = new SDL::Text(renderer, "$50", "Montserrat-Regular.ttf", 20, 255,255,255);
    resources.addTexture("grass","images/grass.png");
    SDL::Texture* grass = resources.getTexture("grass");
    resources.addTexture("school","images/school.png");
    SDL::Texture* school = resources.getTexture("school");
    Cell defaultTile (grass);
    Cell schoolTile (school);
    SDL::Texture* car = resources.getTexture("car");
    Cell carTile (car);
    GameGrid grid (16,16,defaultTile);
    int initTime = SDL::getTicks();
    std::string fpsStr;
    std::string mouseStr;
    std::string tileStr;
    Cell currentTile = schoolTile;
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
                else if(e.key.keysym.sym == SDLK_1){
                    currentTile = schoolTile;
                }else if(e.key.keysym.sym == SDLK_2){
                    currentTile = carTile;
                }
            }
            if(e.type == SDL_MOUSEBUTTONDOWN){
                SDL::getMouseState(&x,&y);
                if(grid.isFree(y/(640/16),x/(640/16))) {
                    grid.setTile(y / (640 / 16), x / (640 / 16), currentTile);
                    prices.push_back(new Price(price, x, y));
                }
            }
            if(e.type == SDL_MOUSEMOTION){
                SDL::getMouseState(&x,&y);
                mouseStr = std::to_string(x);
                mouseStr += " , ";
                mouseStr += std::to_string(y);
            }
        }
        renderer -> setColor(0,0,0,255);
        renderer -> clear();

        for (int k = 0; k < 16; ++k) {
            for (int i = 0; i < 16; ++i) {
                grass -> render(i*(640/16),k*(640/16),(640/16),(640/16));
            }
        }

        //resources.getTexture("car")->render(0,0,SCREEN_WIDTH,SCREEN_HEIGHT);
        grid.draw();
        //drawGrid(renderer, 10);

        int j = 0;


        std::vector<Price*> newprices;
        for(int i = 0; i < prices.size(); i++){
            prices[i]->draw();
            if(prices[i]->alive()){
                newprices.push_back(prices[i]);
            }
        }
        prices = newprices;

        SDL::getMouseState(&x,&y);
        cursor ->render(x,y,32,32);
        frames++;
        int t1 = SDL::getTicks();
        float fps = (float)frames / ((float)(t1 - initTime) / 1000);
        fpsStr = std::to_string(fps);
        SDL::Text debugText (renderer,fpsStr + "\n" + mouseStr,"Montserrat-Regular.ttf",10,0,255,0);
        debugText.render(0,0);
        //printf("char %s, %i","a b",' ');
        renderer->present();
        if(t1 - t0 < 1000/30){
            SDL::delay(1000/30 - (t1-t0));
        }
    }
    SDL::quit();

//    bool quit = false;
//    SDL_Event e;
//    int alpha = 0;

//    SDL_Rect pos = {150,150,266,451};
//    int angle = 0;
//    int startTime = 0;
//    int frames = 0;
//    SDL_Rect camera = {0,0, SCREEN_WIDTH, SCREEN_HEIGHT};
//    std::string mText;
//    SDL_StartTextInput();
//
//    SDL_ShowCursor(0);
//    SDL_Rect cursorRect = {0,0,32,32};
//
//    int x;
//    int y;
//    int g = 50;
//    int currentSprite = SPRITE_BALL;
//    std::vector<SDL_Rect> rects;
//    std::vector<int> figs;
//    figs.push_back(SPRITE_BALL);
//    while (!quit) {
//
//        int start = SDL_GetTicks();
//        while (SDL_PollEvent(&e) != 0) {
//            if (e.type == SDL_MOUSEMOTION){
//                int x, y;
//                SDL_GetMouseState(&x,&y);
//                SDL_Rect mRect = {x/g*g,y/g*g,50,50};
//                if(rects.size()==0)rects.push_back(mRect);
//                rects[0] = mRect;
//            }
//            if (e.type == SDL_MOUSEBUTTONDOWN){
//                int x, y;
//                SDL_GetMouseState(&x,&y);
//                SDL_Rect mRect = {x/g*g,y/g*g,50,50};
//                rects.push_back(mRect);
//                figs.push_back(currentSprite);
//            }
//            //User requests quit
//            if(e.type == SDL_KEYDOWN){
//                std::cout << "Pressed key" << std::endl;
//                if(e.key.keysym.sym == SDLK_1){
//                    currentSprite = SPRITE_BALL;
//                    std::cout << "Pressed key 1" << std::endl;
//                }
//                if(e.key.keysym.sym == SDLK_2){
//                    currentSprite = SPRITE_HOUSE;
//                    std::cout << "Pressed key 2" << std::endl;
//                }
//                if(e.key.keysym.sym == SDLK_3){
//                    currentSprite = SPRITE_CAR;
//                    std::cout << "Pressed key 3" << std::endl;
//                }
//                figs[0] = currentSprite;
//            }
//            if (e . type == SDL_QUIT) {
//                quit = true;
//            }
//
//            /*else if (e . type == SDL_TEXTINPUT) {
//                Mix_PlayChannel( -1, sound, 0 );
//                mText += e.text.text;
//
//            }
//            else if (e . type == SDL_KEYDOWN) {
//                const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
//                if(keyboard_state_array[SDL_SCANCODE_UP]){
//                        pos.y--;
//                    if(pos.y < 0) pos.y = 0;
//                }
//                if(keyboard_state_array[SDL_SCANCODE_DOWN]){
//                    pos.y++;
//                    if(pos.y > LEVEL_HEIGHT) pos.y = LEVEL_HEIGHT;
//                }
//                if(keyboard_state_array[SDL_SCANCODE_RIGHT]){
//                    pos.x+=1;
//                    angle++;
//                    if(pos.x > LEVEL_WIDTH) pos.x = LEVEL_WIDTH;
//                }
//                else if(keyboard_state_array[SDL_SCANCODE_LEFT]){
//                    pos.x -= 1;
//                    angle--;
//                    if(pos.x < 0) pos.x = 0;
//                }
//                if(keyboard_state_array[SDL_SCANCODE_W]){
//                    camera.y--;
//                    if(camera.y < 0) camera.y = 0;
//                }
//                if(keyboard_state_array[SDL_SCANCODE_S]){
//                    camera.y++;
//                    if(camera.y > LEVEL_HEIGHT - camera.h) camera.y = LEVEL_HEIGHT - camera.h;
//                }
//                if(keyboard_state_array[SDL_SCANCODE_D]){
//                    camera.x++;
//                    if(camera.x > LEVEL_WIDTH - camera.w) camera.x = LEVEL_WIDTH - camera.w;
//                }
//                if(keyboard_state_array[SDL_SCANCODE_A]){
//                    camera.x--;
//                    if(camera.x < 0) camera.x = 0;
//                }
//                if(keyboard_state_array[SDL_SCANCODE_BACKSPACE]){
//                    if(mText.size() > 0) {
//                        mText.pop_back();
//                        Mix_PlayChannel( -1, sound, 0 );
//                    }
//                }
//                if(keyboard_state_array[SDL_SCANCODE_ESCAPE]){
//                    quit = true;
//                    break;
//                }
//            }*/
//
//        }
//        //Clear screen
//        SDL::Renderer* renderer = window1 -> getRenderer();
//
//        SDL_RenderClear( renderer );
//
//        SDL_Rect rect = {100,100,300,300};
//        //SDL_RenderSetViewport(renderer,&rect);
//
//        //Render texture to screen
//        SDL_Rect clip = {50,50,100,100};
//        SDL_Rect print;
//        print.x = pos.x - camera.x;
//        print.y = pos.y - camera.y;
//        print.w = pos.w;
//        print.h = pos.h;
//        angle = 0;
//
//        SDL_Rect bg = {-camera.x,-camera.y,LEVEL_WIDTH, LEVEL_HEIGHT};
//
//        SDL_RenderCopy(renderer, bground->getTexture(), NULL, &bg);
//        SDL_SetRenderDrawColor(renderer,0,0,0,0);
//
//        drawGrid(renderer,g);
//        //SDL_RenderCopyEx( renderer, image -> getTexture(), NULL, &print, angle,NULL, SDL_FLIP_NONE);
//        for (int i = 0; i < rects . size(); ++i) {
//            SDL_RenderCopy(renderer, sprites[figs[i]]->getTexture(), NULL, &rects[i]);
//        }
//
//        //Update screen
//
//        SDL_GetMouseState(&x, &y);
//
//        cursorRect.x = x;
//        cursorRect.y = y;
//        SDL_RenderCopy(renderer, cursor-> getTexture(), NULL, &cursorRect);
//
//        SDL_RenderPresent( renderer );
//
//        frames++
//        //std::cout << (float)frames/(SDL_GetTicks()/1000) << " fps"<< std::endl;
//        if(SDL_GetTicks() - start < 1000/60){
//            SDL_Delay(1000/60-(SDL_GetTicks() - start ));
//        }
//    }
//    SDL_RemoveTimer( timerID );
//    SDL_StopTextInput();

}
