#include <iostream>
#include "GameController.h"
#include "Grid.h"

// Game default settings
const int DEFAULT_HEIGHT = 4;
const int DEFAULT_WIDTH = 4;
const int DEFAULT_NUMBER_OF_MINES = 4;

GameController::GameController() : GameController(DEFAULT_HEIGHT, DEFAULT_WIDTH, DEFAULT_NUMBER_OF_MINES){};

GameController::GameController(int height, int width, int numberOfMines) : m_grid(Grid({height, width}, numberOfMines)), m_cli(CLI(m_grid)), m_gameState(init), m_hasLost(false)
{
}

GameController::~GameController()
{
}

// run is the main game loop.
void GameController::run()
{
    initialiseGame();
    m_gameState = gameplay;
    while (m_gameState == gameplay)
    {
        update();
    }
    endGame();
}

void GameController::initialiseGame()
{
    m_cli.initialiseGame();
    m_grid.initialise();
}

void GameController::update()
{
    m_cli.update();
    processNextMove();
}

void GameController::endGame()
{
    m_grid.revealAllCells();
    m_cli.endGame(m_hasLost);
}

void GameController::processNextMove()
{
    auto move = m_cli.promptNextMove();
    m_hasLost = m_grid.processMove(move);
    if (m_hasLost || m_grid.getNumberOfRemainingEmptyCells() == 0)
    {
        m_gameState = end;
    }
}