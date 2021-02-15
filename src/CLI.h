#pragma once
#include <string>
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
    Vector2 promptNextMove();
    int promptInt(std::string prompt);
};