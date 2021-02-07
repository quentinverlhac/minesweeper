#pragma once
#include "Grid.h"

class CLI
{
private:
    Grid &m_grid;

public:
    CLI(Grid &grid);
    ~CLI();
    void update();
    void displayGrid();
    char getCellChar(Cell *cell);
    void promptNextMove();
};