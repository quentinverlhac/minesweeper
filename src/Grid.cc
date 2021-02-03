#include "Grid.h"

Grid::Grid(Vector2 dimensions, int numberOfMines) : m_dimensions(dimensions), m_numberOfMines(numberOfMines){};

Grid::~Grid(){};

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
