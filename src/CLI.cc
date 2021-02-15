#include <iostream>
#include <sstream>
#include "CLI.h"

const char DEFAULT_UNREVEALED_CELL = '.';
const char FLAGGED_CELL = '?';
const char MINE = '*';

CLI::CLI(Grid &grid) : m_grid(grid){};

CLI::~CLI(){};

void CLI::update()
{
    this->displayGrid();
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

int CLI::promptInt(std::string prompt)
{
    int output;
    for (std::string line; std::cout << prompt && std::getline(std::cin, line);)
    {
        std::istringstream iss(line);
        if (iss >> output && iss.get() == EOF)
        {
            return output;
        }
        else
        {
            std::cerr << "Cannot parse input. Received '" << line << "'. Should be an integer." << std::endl;
        }
    }
}

Vector2 CLI::promptNextMove()
{
    std::cout << "Next move ?" << std::endl;
    int row = this->promptInt("Enter a row: ");
    int column = this->promptInt("Enter a column: ");
    return {row, column};
};