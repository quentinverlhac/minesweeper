#pragma once
#include "Grid.h"
#include "CLI.h"

enum GameState
{
    init,
    gameplay,
    end,
};

class GameController
{
private:
    GameState m_gameState;
    bool m_hasLost;
    Grid m_grid;
    CLI m_cli;

public:
    GameController();
    GameController(int height, int width, int numberOfMines);
    ~GameController();
    void run();
    void processNextMove();
};