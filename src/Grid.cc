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

void Grid::initializeMines()
{
}
