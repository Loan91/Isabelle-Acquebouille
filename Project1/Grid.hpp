#ifndef GRID_HPP
#define GRID_HPP
#pragma once
#include "includes.hpp"

const int GRID_WIDTH = 20;
const int GRID_HEIGHT = 15;
const int CELL_SIZE = 40;

struct Cell {
    bool walkable;
    Vector2f position;
    RectangleShape shape;
};

class Grid {
public:
    Grid();
    void loadFromFile(const string& filename);
    void draw(RenderWindow& window);
    Cell& getCell(int x, int y);
private:
    vector<vector<Cell>> cells;
};

#endif      