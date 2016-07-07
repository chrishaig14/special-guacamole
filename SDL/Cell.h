//
// Created by chris on 04/07/16.
//

#ifndef CITY_TILE_H
#define CITY_TILE_H

#include "Texture.h"

class Cell {
    SDL::Texture* texture;
public:
    Cell(SDL::Texture* texture){
        this -> texture = texture;
    }
    void draw(int x, int y){
        if(texture -> getAlpha() != 255) texture -> setAlpha(255);
        texture->render(x,y,640/16,640/16);
    }
};


#endif //CITY_TILE_H
