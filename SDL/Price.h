//
// Created by chris on 04/07/16.
//

#ifndef CITY_PRICE_H
#define CITY_PRICE_H

#include "Text.h"

class Price {
    int t0;
    int t1;
    int life;
    int x0;
    int y0;
    int accel;
    SDL::Texture *text;
public:

    Price(SDL::Texture* texture, int x, int y){
        accel = 50;
        t0 = 0;
        t1 = 0;
        x0 = x;
        y0 = y;
        life = 1000;
        text = texture;
    }

    bool alive(){
        return t1 - t0 < life;
    }

    void draw(){
        if(t0 == 0){
            t0 = SDL::getTicks();
        }
        t1 = SDL::getTicks();
        int x = x0;
        int dt = (t1 - t0);
        int alpha = 255 - 255*(((float)dt/1000));
        alpha = alpha < 0?0:alpha;
        int y = y0 -((float)dt/1000)*5- 500*(((float)dt/1000))*(((float)dt/1000))/2;
        //int y = y0 - accel*(float)(dt/1000)*(float)(dt/1000)/2;
        text -> setAlpha(alpha);
        text -> render(x,y);
    }

    ~Price(){
        delete text;
    }
};


#endif //CITY_PRICE_H
