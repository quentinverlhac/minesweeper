#pragma once
#include <vector>
#include "Cell.h"

struct Vector2
{
    int i; // height / row
    int j; // width / column
    // The following set of functions are utils to get adjacent coordinates.
    // Make sure that the coordinates stay within the grid when using these.
    Vector2 topLeft() { return {i - 1, j - 1}; };
    Vector2 top() { return {i - 1, j}; };
    Vector2 topRight() { return {i - 1, j + 1}; };
    Vector2 left() { return {i, j - 1}; };
    Vector2 right() { return {i, j + 1}; };
    Vector2 bottomLeft() { return {i + 1, j - 1}; };
    Vector2 bottom() { return {i + 1, j}; };
    Vector2 bottomRight() { return {i + 1, j + 1}; };
};

class Grid
{
    Vector2 m_dimensions;
    int m_numberOfMines;
    Cell *m_cells; // TODO use smart_pointers to protect this

public:
    Grid(Vector2 dimensions, int numberOfMines);
    ~Grid();
    Cell *getCell(Vector2 coordinates);
    std::vector<Vector2> getAdjacentCoordinates(Vector2 coordinates, bool includeDiagonals);
    Vector2 getDimensions();
    int getNumberOfCells();
    int getNumberOfMines();
    void initializeMines();
    bool processMove(Vector2 coordinates);
    int countAdjacentMines(Vector2 coordinates);
};