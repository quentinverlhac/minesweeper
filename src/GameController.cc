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
    this->initialiseGame();
    this->m_gameState = gameplay;
    while (this->m_gameState == gameplay)
    {
        this->update();
    }
    this->endGame();
}

void GameController::initialiseGame()
{
    this->m_cli.initialiseGame();
    this->m_grid.initializeMines();
}

void GameController::update()
{
    this->m_cli.update();
    this->processNextMove();
}

void GameController::endGame()
{
    this->m_cli.endGame(this->m_hasLost);
}

void GameController::processNextMove()
{
    auto move = this->m_cli.promptNextMove();
    this->m_hasLost = this->m_grid.processMove(move);
    if (this->m_hasLost)
    {
        this->m_gameState = end;
    }
}