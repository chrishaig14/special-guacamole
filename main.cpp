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

void drawGrid(SDL_Renderer* renderer, int g){
    for (int i = 0; i < SCREEN_WIDTH/g; ++i) {
        SDL_RenderDrawLine(renderer,i*g,0,i*g,SCREEN_HEIGHT);
    }
    for (int i = 0; i < SCREEN_HEIGHT/g; ++i) {
        SDL_RenderDrawLine(renderer,0,i*g,SCREEN_WIDTH,i*g);
    }
}

int main(int argc, char *args[]) {
    SDL::init();
    SDL::Window *window1 = new SDL::Window(640, 480);
    window1 -> setTitle("Título");

    SDL_TimerID timerID = SDL_AddTimer( 5000, callback, NULL);
    SDL::Texture *ball = new SDL::Texture();
    ball -> loadImage(window1->getRenderer(),"images/balloon.jpg");
    SDL::Texture *house = new SDL::Texture();
    house -> loadImage(window1->getRenderer(),"images/house.png");
    SDL::Texture *car = new SDL::Texture();
    car -> loadImage(window1->getRenderer(),"images/car.png");

    SDL::Texture* sprites[3] = {ball, house, car};

    for (int j = 0; j < 3; ++j) {
        SDL_Texture* texture = sprites[j] -> getTexture();
        int w, h;
        SDL_QueryTexture(texture, NULL, NULL,&w,&h);
        std::cout << "Texture size: " << w << "," << h << std::endl;

    }

    SDL::Texture * bground = new SDL::Texture();

    bground-> loadImage(window1->getRenderer(),"images/background.png");

//	SDL_Delay( 20000 );
    bool quit = false;
    SDL_Event e;
    int alpha = 0;
   // SDL_SetTextureColorMod( image -> getTexture(), 23, 129, 244 );
    //SDL_SetTextureBlendMode( image -> getTexture(), SDL_BLENDMODE_BLEND);
    SDL_Rect pos = {150,150,266,451};
    int angle = 0;
    int startTime = 0;
    int frames = 0;
    SDL_Rect camera = {0,0, SCREEN_WIDTH, SCREEN_HEIGHT};
    std::string mText;
    SDL_StartTextInput();
    Mix_Chunk* sound = NULL;
    sound = Mix_LoadWAV( "audio/blop.wav" );
    Mix_Music* music = NULL;
    music = Mix_LoadMUS( "audio/music.mp3" );
    Mix_PlayMusic(music,-1);
    SDL_ShowCursor(0);
    SDL::Texture * cursor = new SDL::Texture();
    SDL_Rect cursorRect = {0,0,32,32};
    cursor -> loadImage(window1->getRenderer(),"images/cursor.png");
    int x;
    int y;
    int g = 50;
    int currentSprite = SPRITE_BALL;
    std::vector<SDL_Rect> rects;
    std::vector<int> figs;
    figs.push_back(SPRITE_BALL);
    while (!quit) {

        int start = SDL_GetTicks();
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_MOUSEMOTION){
                int x, y;
                SDL_GetMouseState(&x,&y);
                SDL_Rect mRect = {x/g*g,y/g*g,50,50};
                if(rects.size()==0)rects.push_back(mRect);
                rects[0] = mRect;
            }
            if (e.type == SDL_MOUSEBUTTONDOWN){
                int x, y;
                SDL_GetMouseState(&x,&y);
                SDL_Rect mRect = {x/g*g,y/g*g,50,50};
                rects.push_back(mRect);
                figs.push_back(currentSprite);
            }
            //User requests quit
            if(e.type == SDL_KEYDOWN){
                std::cout << "Pressed key" << std::endl;
                if(e.key.keysym.sym == SDLK_1){
                    currentSprite = SPRITE_BALL;
                    std::cout << "Pressed key 1" << std::endl;
                }
                if(e.key.keysym.sym == SDLK_2){
                    currentSprite = SPRITE_HOUSE;
                    std::cout << "Pressed key 2" << std::endl;
                }
                if(e.key.keysym.sym == SDLK_3){
                    currentSprite = SPRITE_CAR;
                    std::cout << "Pressed key 3" << std::endl;
                }
                figs[0] = currentSprite;
            }
            if (e . type == SDL_QUIT) {
                quit = true;
            }

            /*else if (e . type == SDL_TEXTINPUT) {
                Mix_PlayChannel( -1, sound, 0 );
                mText += e.text.text;

            }
            else if (e . type == SDL_KEYDOWN) {
                const Uint8 *keyboard_state_array = SDL_GetKeyboardState(NULL);
                if(keyboard_state_array[SDL_SCANCODE_UP]){
                        pos.y--;
                    if(pos.y < 0) pos.y = 0;
                }
                if(keyboard_state_array[SDL_SCANCODE_DOWN]){
                    pos.y++;
                    if(pos.y > LEVEL_HEIGHT) pos.y = LEVEL_HEIGHT;
                }
                if(keyboard_state_array[SDL_SCANCODE_RIGHT]){
                    pos.x+=1;
                    angle++;
                    if(pos.x > LEVEL_WIDTH) pos.x = LEVEL_WIDTH;
                }
                else if(keyboard_state_array[SDL_SCANCODE_LEFT]){
                    pos.x -= 1;
                    angle--;
                    if(pos.x < 0) pos.x = 0;
                }
                if(keyboard_state_array[SDL_SCANCODE_W]){
                    camera.y--;
                    if(camera.y < 0) camera.y = 0;
                }
                if(keyboard_state_array[SDL_SCANCODE_S]){
                    camera.y++;
                    if(camera.y > LEVEL_HEIGHT - camera.h) camera.y = LEVEL_HEIGHT - camera.h;
                }
                if(keyboard_state_array[SDL_SCANCODE_D]){
                    camera.x++;
                    if(camera.x > LEVEL_WIDTH - camera.w) camera.x = LEVEL_WIDTH - camera.w;
                }
                if(keyboard_state_array[SDL_SCANCODE_A]){
                    camera.x--;
                    if(camera.x < 0) camera.x = 0;
                }
                if(keyboard_state_array[SDL_SCANCODE_BACKSPACE]){
                    if(mText.size() > 0) {
                        mText.pop_back();
                        Mix_PlayChannel( -1, sound, 0 );
                    }
                }
                if(keyboard_state_array[SDL_SCANCODE_ESCAPE]){
                    quit = true;
                    break;
                }
            }*/

        }
        //Clear screen
        SDL_Renderer* renderer = window1 -> getRenderer();

        SDL_RenderClear( renderer );

        SDL_Rect rect = {100,100,300,300};
        //SDL_RenderSetViewport(renderer,&rect);

        //Render texture to screen
        SDL_Rect clip = {50,50,100,100};
        SDL_Rect print;
        print.x = pos.x - camera.x;
        print.y = pos.y - camera.y;
        print.w = pos.w;
        print.h = pos.h;
        angle = 0;

        SDL_Rect bg = {-camera.x,-camera.y,LEVEL_WIDTH, LEVEL_HEIGHT};

        SDL_RenderCopy(renderer, bground->getTexture(), NULL, &bg);
        SDL_SetRenderDrawColor(renderer,0,0,0,0);

        drawGrid(renderer,g);
        //SDL_RenderCopyEx( renderer, image -> getTexture(), NULL, &print, angle,NULL, SDL_FLIP_NONE);
        for (int i = 0; i < rects . size(); ++i) {
            SDL_RenderCopy(renderer, sprites[figs[i]]->getTexture(), NULL, &rects[i]);
        }
        //SDL_RenderCopy( renderer, image -> getTexture(), NULL, &pos);
//        SDL_Rect fillRect = {0,0,200,200};
//        SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
//        SDL_RenderFillRect(renderer,&fillRect);
//        SDL_SetRenderDrawColor( renderer, 0x00, 0xF0, 0xF0, 0xFF );
//        SDL_RenderDrawRect(renderer,&fillRect);
//        SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
//        SDL_RenderDrawLine(renderer,0,0,100,200);
//        SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0xFF, 0xFF );
//        SDL_RenderDrawPoint(renderer,100,250);


        TTF_Font *gFont = NULL;
        gFont = TTF_OpenFont( "lazy.ttf", 24 );
        if( gFont == NULL )
        {
            printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        }
        SDL_Color color = {0,0,255};
        TTF_SetFontStyle(gFont,TTF_STYLE_BOLD);
        SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped( gFont, "Hello\npepe", color,200);
        SDL_Rect rrr;
        SDL_GetClipRect(textSurface, &rrr);
        SDL_Texture* mTexture = SDL_CreateTextureFromSurface( renderer, textSurface );
        SDL_FreeSurface( textSurface );
        SDL_RenderCopy( renderer, mTexture, NULL, &rrr);
        TTF_CloseFont( gFont );
        SDL_DestroyTexture(mTexture);
        //Update screen

        SDL_GetMouseState(&x, &y);

        cursorRect.x = x;
        cursorRect.y = y;
        SDL_RenderCopy(renderer, cursor-> getTexture(), NULL, &cursorRect);

        SDL_RenderPresent( renderer );

        frames++;
        //std::cout << (float)frames/(SDL_GetTicks()/1000) << " fps"<< std::endl;
        if(SDL_GetTicks() - start < 1000/60){
            SDL_Delay(1000/60-(SDL_GetTicks() - start ));
        }
    }
    SDL_RemoveTimer( timerID );
    Mix_FreeChunk( sound );
    Mix_FreeMusic( music );
    SDL_StopTextInput();
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
