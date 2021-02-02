#include "Grid.h"

Grid::Grid(Vector2 dimensions) : dimensions(dimensions){};

Grid::~Grid(){};

Vector2 Grid::getDimensions()
{
    return this->dimensions;
}