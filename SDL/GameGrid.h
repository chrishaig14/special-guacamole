//
// Created by chris on 04/07/16.
//

#ifndef CITY_GAMEGRID_H
#define CITY_GAMEGRID_H


#include <array>
#include <vector>
#include <iostream>
#include "Cell.h"

class GameGrid {
    std::vector<std::vector<Cell*>> grid;
    int w;
    int h;
public:
    GameGrid(int w, int h, Cell defaultTile){
        this -> w = w;
        this -> h = h;
        for (int i = 0; i < w; ++i) {
            grid.push_back(std::vector<Cell*>());
            for (int j = 0; j < h; ++j) {
                grid[i].push_back(NULL);
            }
        }
    }
    void setTile(int i, int j, Cell tile){
        if(grid[i][j] != NULL) return;
        grid[i][j] = new Cell(tile);
    }
    bool isFree(int i , int j){
        return grid[i][j] == NULL;
    }
    void draw(){
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if(grid[i][j] != NULL)grid[i][j]->draw(j*(640/w),(640/h)*i);
            }
        }
    }
    ~GameGrid(){
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[i].size(); ++j) {
                if(grid[i][j] != NULL){
                    delete grid[i][j];
                }
            }
        }
    }
};


#endif //CITY_GAMEGRID_H
