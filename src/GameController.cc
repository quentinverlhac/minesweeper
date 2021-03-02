#include <iostream>
#include "GameController.h"
#include "Grid.h"

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
    std::cout << "-- Minesweeper --" << std::endl;
    std::cout << "Dimensions: " << this->m_grid.getDimensions().i << " x " << this->m_grid.getDimensions().j << std::endl;
    std::cout << "Number of mines: " << this->m_grid.getNumberOfMines() << std::endl;
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
    std::cout << "Move: " << move.i << "," << move.j << std::endl;
    this->m_hasLost = this->m_grid.processMove(move);
    if (this->m_hasLost)
    {
        this->m_gameState = end;
    }
}