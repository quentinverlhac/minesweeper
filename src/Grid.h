#pragma once

struct Vector2
{
    int i; // height
    int j; // width
};

class Grid
{
    Vector2 m_dimensions;
    int m_numberOfMines;

public:
    Grid(Vector2 dimensions, int numberOfMines);
    ~Grid();
    Vector2 getDimensions();
    int getNumberOfMines();
    void initializeMines();
};