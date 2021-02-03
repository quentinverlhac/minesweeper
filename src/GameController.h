#pragma once
#include "Grid.h"

class GameController
{
private:
    Grid grid;

public:
    GameController();
    GameController(int height, int width, int numberOfMines);
    ~GameController();
    void run();
};