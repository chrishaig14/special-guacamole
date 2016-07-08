//
// Created by chris on 05/07/16.
//

#ifndef CITY_CITY_H
#define CITY_CITY_H


#include "GameGrid.h"

class City {
    GameGrid grid;
public:
    void update(float dt){

    }
    void draw(){
        grid.draw();
    }
};


#endif //CITY_CITY_H
