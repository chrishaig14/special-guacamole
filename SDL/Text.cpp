//
// Created by chris on 03/07/16.
//

#include <iostream>
#include "Text.h"

SDL::Text::Text(SDL::Renderer* renderer, std::string text, std::string font, int size, int r, int g, int b) {
    this -> renderer = renderer;
    TTF_Font *gFont = NULL;
    gFont = TTF_OpenFont(font.c_str(),size);
    if( gFont == NULL )
    {
        printf( "Failed to load font! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    SDL_Color color = {r,g,b};
    //TTF_SetFontStyle(gFont,TTF_STYLE_BOLD);
    SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped( gFont, text.c_str(), color,100);
    SDL_Rect rrr;
    SDL_GetClipRect(textSurface, &rrr);
    texture = SDL_CreateTextureFromSurface( renderer->getRenderer(), textSurface );
    SDL_FreeSurface( textSurface );

    TTF_CloseFont( gFont );
}

SDL::Text::~Text() {
    SDL_DestroyTexture(texture);
}