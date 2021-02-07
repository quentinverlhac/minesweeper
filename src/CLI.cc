#include <iostream>
#include "CLI.h"

const char DEFAULT_UNREVEALED_CELL = '.';
const char FLAGGED_CELL = '?';
const char MINE = '*';

CLI::CLI(Grid &grid) : m_grid(grid){};

CLI::~CLI(){};

void CLI::update()
{
    displayGrid();
};

void CLI::displayGrid()
{
    for (int i = 0; i < this->m_grid.getDimensions().i; i++)
    {
        for (int j = 0; j < this->m_grid.getDimensions().j; j++)
        {
            Vector2 coordinates = {i, j};
            Cell *cell = m_grid.getCell(coordinates);
            std::cout << getCellChar(cell) << ' ';
        }
        std::cout << std::endl;
    }
};

char CLI::getCellChar(Cell *cell)
{
    if (cell->isRevealed)
    {
        // mine or hint value
        if (cell->isMine)
        {
            return MINE;
        }
        return '0' + cell->hintLabel; // this returns the hint label as a char, since it is less than 8
    }
    else
    {
        // flagged or default
        if (cell->isFlagged)
        {
            return FLAGGED_CELL;
        }
        return DEFAULT_UNREVEALED_CELL;
    }
};

void CLI::promptNextMove(){};