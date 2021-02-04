#include <random>
#include <unordered_set>
#include "Grid.h"

Grid::Grid(Vector2 dimensions, int numberOfMines) : m_dimensions(dimensions), m_numberOfMines(numberOfMines)
{
    this->m_cells = new Cell[this->m_dimensions.i * this->m_dimensions.j];
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

Vector2 Grid::getDimensions()
{
    return this->m_dimensions;
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
        if (set.find(rdm) != set.end())
        {
            // rdm is not in the set
            set.insert(rdm);
            this->m_cells[rdm].isMine = true;
        }
        else
        {
            // rdm is in the set, but i is not
            set.insert(i);
            this->m_cells[i].isMine = true;
        }
    }
}
