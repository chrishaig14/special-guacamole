//
// Created by chris on 04/07/16.
//

#ifndef CITY_TILE_H
#define CITY_TILE_H

#include <vector>
#include <iostream>
#include "Texture.h"
#include "screen.h"

class Cell {
    SDL::Texture* texture;
    SDL::Texture* textureDead;
    SDL::Texture* textureAlive;
    std::vector<Cell*> neighbours;
    bool alive;
    bool nextState;
public:
    Cell(SDL::Texture* textureAlive, SDL::Texture* textureDead){
        this -> textureDead = textureDead;
        this -> texture = textureDead;
        this -> textureAlive = textureAlive;
        this -> alive = false;
        this -> nextState = false;
    }

    void setLive(){
        alive = true;
        texture = textureAlive;
    }
    void setDead(){
        alive = false;
        texture = textureDead;
    }

    void addNeighbour(Cell* cell){
        neighbours.push_back(cell);
    }

    bool applyNextState(){
        if(nextState)
            setLive();
        else setDead();
        return alive;
    }

    bool getNextState() {
        int aliveCount = 0;
        for (int i = 0; i < neighbours.size(); ++i) {
            aliveCount += neighbours[i]->alive?1:0;
        }
        if(alive){
            if (aliveCount == 4 || aliveCount == 3) {
                nextState = true;
                return true;
            } else {
                nextState = false;
                return false;
            }
        } else {
            if(aliveCount == 4){
                nextState = true;
                return true;
            }
            nextState = false;
            return false;
        }
    }

    int getNeighbours() {
        int aliveCount = 0;
        std::cout << "NEXT STATE: " << (getNextState()?"ALIVE":"DEAD" )<< std::endl;
        for (int i = 0; i < neighbours.size(); ++i) {
            aliveCount += neighbours[i]->alive ? 1 : 0;
        }
        return aliveCount;
    }
    void draw(int x, int y){
        if(texture -> getAlpha() != 255) texture -> setAlpha(255);
        texture->render(x,y,SCREEN_WIDTH/GRID,SCREEN_HEIGHT/GRID);
    }
};


#endif //CITY_TILE_H
