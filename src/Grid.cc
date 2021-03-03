#include <random>
#include <unordered_set>
#include <vector>
#include "Grid.h"

Grid::Grid(Vector2 dimensions, int numberOfMines) : m_dimensions(dimensions), m_numberOfMines(numberOfMines)
{
    this->m_cells = new Cell[this->getNumberOfCells()];
};

Grid::~Grid()
{
    delete[] this->m_cells;
};

// getCell returns a pointer to the target cell if coordinates are within the grid dimensions, or a pointer to null otherwise.
Cell *Grid::getCell(Vector2 coordinates)
{
    if (coordinates.i >= this->m_dimensions.i || coordinates.j >= m_dimensions.j)
    {
        return nullptr;
    }
    return &(this->m_cells[coordinates.i * m_dimensions.j + coordinates.j]);
}

// getAdjacentCells returns a vector of pointers to the cells that are adjacent to the given coordinates. It takes the Grid dimensions into account.
std::vector<Cell *> Grid::getAdjacentCells(Vector2 coordinates, bool includeDiagonals)
{
    std::vector<Cell *> adjacentCells = std::vector<Cell *>(3); // 3 is the minimum number of cells to return
    if (coordinates.i == 0)
    {
        // top
        if (coordinates.j == 0)
        {
            // top left
            adjacentCells.push_back(this->getCell(coordinates.right()));
            adjacentCells.push_back(this->getCell(coordinates.bottom()));
            if (includeDiagonals)
            {
                adjacentCells.push_back(this->getCell(coordinates.bottomRight()));
            }
            return adjacentCells;
        }
        else if (coordinates.j == this->m_dimensions.j - 1)
        {
            // top right
            adjacentCells.push_back(this->getCell(coordinates.left()));
            adjacentCells.push_back(this->getCell(coordinates.bottom()));
            if (includeDiagonals)
            {
                adjacentCells.push_back(this->getCell(coordinates.bottomLeft()));
            }
            return adjacentCells;
        }
        else
        {
            // top middle
            adjacentCells.push_back(this->getCell(coordinates.left()));
            adjacentCells.push_back(this->getCell(coordinates.right()));
            adjacentCells.push_back(this->getCell(coordinates.bottom()));
            if (includeDiagonals)
            {
                adjacentCells.push_back(this->getCell(coordinates.bottomLeft()));
                adjacentCells.push_back(this->getCell(coordinates.bottomRight()));
            }
            return adjacentCells;
        }
    }
    else if (coordinates.i == this->m_dimensions.i - 1)
    {
        // bottom
        if (coordinates.j == 0)
        {
            // bottom left
            adjacentCells.push_back(this->getCell(coordinates.top()));
            adjacentCells.push_back(this->getCell(coordinates.right()));
            if (includeDiagonals)
            {
                adjacentCells.push_back(this->getCell(coordinates.topRight()));
            }
            return adjacentCells;
        }
        else if (coordinates.j == this->m_dimensions.j - 1)
        {
            // bottom right
            adjacentCells.push_back(this->getCell(coordinates.top()));
            adjacentCells.push_back(this->getCell(coordinates.left()));
            if (includeDiagonals)
            {
                adjacentCells.push_back(this->getCell(coordinates.topLeft()));
            }
            return adjacentCells;
        }
        else
        {
            // bottom middle
            adjacentCells.push_back(this->getCell(coordinates.top()));
            adjacentCells.push_back(this->getCell(coordinates.left()));
            adjacentCells.push_back(this->getCell(coordinates.right()));
            if (includeDiagonals)
            {
                adjacentCells.push_back(this->getCell(coordinates.topLeft()));
                adjacentCells.push_back(this->getCell(coordinates.topRight()));
            }
            return adjacentCells;
        }
    }
    else
    {
        // middle
        if (coordinates.j == 0)
        {
            // middle left
            adjacentCells.push_back(this->getCell(coordinates.top()));
            adjacentCells.push_back(this->getCell(coordinates.right()));
            adjacentCells.push_back(this->getCell(coordinates.bottom()));
            if (includeDiagonals)
            {
                adjacentCells.push_back(this->getCell(coordinates.topRight()));
                adjacentCells.push_back(this->getCell(coordinates.bottomRight()));
            }
            return adjacentCells;
        }
        else if (coordinates.j == this->m_dimensions.j - 1)
        {
            // middle right
            adjacentCells.push_back(this->getCell(coordinates.top()));
            adjacentCells.push_back(this->getCell(coordinates.left()));
            adjacentCells.push_back(this->getCell(coordinates.bottom()));
            if (includeDiagonals)
            {
                adjacentCells.push_back(this->getCell(coordinates.topLeft()));
                adjacentCells.push_back(this->getCell(coordinates.bottomLeft()));
            }
            return adjacentCells;
        }
        else
        {
            // in the middle
            adjacentCells.push_back(this->getCell(coordinates.top()));
            adjacentCells.push_back(this->getCell(coordinates.left()));
            adjacentCells.push_back(this->getCell(coordinates.right()));
            adjacentCells.push_back(this->getCell(coordinates.bottom()));
            if (includeDiagonals)
            {
                adjacentCells.push_back(this->getCell(coordinates.topLeft()));
                adjacentCells.push_back(this->getCell(coordinates.topRight()));
                adjacentCells.push_back(this->getCell(coordinates.bottomLeft()));
                adjacentCells.push_back(this->getCell(coordinates.bottomRight()));
            }
            return adjacentCells;
        }
    }
}

Vector2 Grid::getDimensions()
{
    return this->m_dimensions;
}

int Grid::getNumberOfCells()
{
    return this->m_dimensions.i * this->m_dimensions.j;
}

int Grid::getNumberOfMines()
{
    return this->m_numberOfMines;
}

// initializeMines uses Floyd sample without replacement algorithm to randomly select m_numberOfMines cells and initialize them as mines
void Grid::initializeMines()
{
    std::unordered_set<int> set;
    auto gen = std::mt19937{std::random_device{}()};
    for (int i = this->m_dimensions.i * this->m_dimensions.j - this->m_numberOfMines; i < this->m_dimensions.i * this->m_dimensions.j; i++)
    {
        int rdm = std::uniform_int_distribution<>(1, i)(gen);
        if (set.find(rdm) == set.end())
        {
            // rdm is not in the set
            set.insert(rdm);
            this->m_cells[rdm].isMine = true;
        }
        else
        {
            // rdm is in the set, but i is not because it can be sampled for the first time
            set.insert(i);
            this->m_cells[i].isMine = true;
        }
    }
}

bool Grid::processMove(Vector2 move)
{
    auto cell = this->getCell(move);
    cell->isRevealed = true;
    if (cell->isMine)
    {
        return true;
    }
    else
    {
        return false;
    }
}
