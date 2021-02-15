#pragma once
#include "Grid.h"
#include "CLI.h"

class GameController
{
private:
    Grid grid;
    CLI m_cli;

public:
    GameController();
    GameController(int height, int width, int numberOfMines);
    ~GameController();
    void run();
    void processNextMove();
};