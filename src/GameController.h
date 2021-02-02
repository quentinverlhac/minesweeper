#pragma once
#include "Grid.h"

class GameController
{
private:
    Grid grid;

public:
    GameController();
    GameController(int height, int width);
    ~GameController();
    void run();
};