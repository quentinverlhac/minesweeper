#pragma once
#include "Cell.h"

struct Vector2
{
    int i; // height / row
    int j; // width / column
};

class Grid
{
    Vector2 m_dimensions;
    int m_numberOfMines;
    Cell *m_cells;

public:
    Grid(Vector2 dimensions, int numberOfMines);
    ~Grid();
    Vector2 getDimensions();
    int getNumberOfCells();
    int getNumberOfMines();
    void initializeMines();
    Cell *getCell(Vector2 coordinates);
};