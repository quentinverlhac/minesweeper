#include <iostream>
#include <memory>
#include <sstream>
#include "CLI.h"

const char DEFAULT_UNREVEALED_CELL = '.';
const char FLAGGED_CELL = '?';
const char MINE = '*';

CLI::CLI(Grid &grid) : m_grid(grid){};

CLI::~CLI(){};

void CLI::initialiseGame()
{
    std::cout << "-- Minesweeper --" << std::endl;
    std::cout << "Dimensions: " << m_grid.getDimensions().i << " x " << m_grid.getDimensions().j << std::endl;
    std::cout << "Number of mines: " << m_grid.getNumberOfMines() << std::endl;
}

void CLI::update()
{
    displayGrid();
};

void CLI::endGame(bool hasLost)
{
    update();
    if (hasLost)
    {
        std::cout << "Game over!" << std::endl;
    }
    else
    {
        std::cout << "You won!" << std::endl;
    }
};

void CLI::displayGrid()
{
    for (int i = 0; i < m_grid.getDimensions().i; i++)
    {
        for (int j = 0; j < m_grid.getDimensions().j; j++)
        {
            Vector2 coordinates = {i, j};
            std::shared_ptr<Cell> cell = m_grid.getCell(coordinates);
            std::cout << getCellChar(cell) << ' ';
        }
        std::cout << std::endl;
    }
};

char CLI::getCellChar(std::shared_ptr<Cell> cell)
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

// promptInt displays the prompt and returns the int input by the user
int CLI::promptInt(std::string prompt)
{
    int output;
    for (std::string line; std::cout << prompt && std::getline(std::cin, line);)
    {
        std::istringstream iss(line);
        if (iss >> output && iss.get() == EOF)
        {
            break;
        }
        else
        {
            std::cerr << "Cannot parse input. Received '" << line << "'. Should be an integer." << std::endl;
        }
    }
    return output;
}

int CLI::promptCoordinate(std::string prompt)
{
    int coordinate = -1;
    do
    {
        coordinate = promptInt(prompt);
        if (coordinate < 0 || coordinate >= m_grid.getDimensions().i)
        {
            std::cout << "Please enter a number within 0 and " << m_grid.getDimensions().i - 1 << std::endl;
        }
    } while (coordinate < 0 || coordinate >= m_grid.getDimensions().i);
    return coordinate;
}

Vector2 CLI::promptNextMove()
{
    std::cout << "Next move ?" << std::endl;
    int row = promptCoordinate("Enter a row: ");
    int column = promptCoordinate("Enter a column: ");
    std::cout << "Move: " << row << "," << column << std::endl;
    return {row, column};
};