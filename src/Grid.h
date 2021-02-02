#pragma once

struct Vector2
{
    int i; // height
    int j; // width
};

class Grid
{
    Vector2 dimensions;

public:
    Grid(Vector2 dimensions);
    ~Grid();
    Vector2 getDimensions();
};