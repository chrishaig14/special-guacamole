//
// Created by chris on 04/07/16.
//

#ifndef CITY_GAMEGRID_H
#define CITY_GAMEGRID_H


#include <array>
#include <vector>
#include <iostream>
#include "Cell.h"
#include "screen.h"

class GameGrid {
    std::vector<std::vector<Cell *>> grid;
    int w;
    int h;
public:
    GameGrid(int w, int h, Cell defaultTile) {
        this->w = w;
        this->h = h;
        for (int i = 0; i < h; i++) {
            grid.push_back(std::vector<Cell *>());
            for (int j = 0; j < w; j++) {
                grid[i].push_back(new Cell(defaultTile));
            }
        }
        for (int i = 0; i < h; i++) {
            std::cout << "|";
            for (int j = 0; j < w; j++) {
                int x = 0;
                if (i > 0 && j > 0) {
                    grid[i][j]->addNeighbour(grid[i - 1][j - 1]); // Top left neighour
                    x++;
                }
                if (i > 0) {
                    grid[i][j]->addNeighbour(grid[i - 1][j]); // Top middle neighbour
                    x++;
                }
                if (i > 0 && j < w - 1) {
                    grid[i][j]->addNeighbour(grid[i - 1][j + 1]); // Top right neighbour
                    x++;
                }
                if (j > 0) {
                    grid[i][j]->addNeighbour(grid[i][j - 1]); // Middle left neighbour
                    x++;
                }
                if (j < w - 1) {
                    grid[i][j]->addNeighbour(grid[i][j + 1]); // Middle right neighbour
                    x++;
                }
                if (i < h - 1 && j > 0) {
                    grid[i][j]->addNeighbour(grid[i + 1][j - 1]); // Botton left neighbour
                    x++;
                }
                if (i < h - 1) {
                    grid[i][j]->addNeighbour(grid[i + 1][j]); // Botton middle neighbour
                    x++;
                }
                if (i < h - 1 && j < w - 1) {
                    grid[i][j]->addNeighbour(grid[i + 1][j + 1]); // Botton right neighbour
                    x++;
                }

                std::cout << x << "|";
            }
            std::cout << std::endl;
        }
    }

    void setTile(int i, int j) {
        grid[i][j]->setLive();
    }

    bool isFree(int i, int j) {
        return grid[i][j] == NULL;
    }

    void update() {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                grid[i][j]->getNextState();
                if (i == 9 && j == 13) {
                    std::cout << "NEXT STATE OF 9,13 is" << grid[i][j]->getNextState() << std::endl;
                }
            }
        }
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {

                grid[i][j]->applyNextState();
            }
        }
    }

    Cell *getCell(int i, int j) {
        return grid[i][j];
    }

    void draw() {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                grid[i][j]->draw(j * (SCREEN_WIDTH / w), (SCREEN_HEIGHT / h) * i);
            }
        }
    }

    ~GameGrid() {
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] != NULL) {
                    delete grid[i][j];
                }
            }
        }
    }
};


#endif //CITY_GAMEGRID_H
