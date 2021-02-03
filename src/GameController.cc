#include <iostream>
#include "GameController.h"
#include "Grid.h"

const int DEFAULT_HEIGHT = 16;
const int DEFAULT_WIDTH = 16;
const int DEFAULT_NUMBER_OF_MINES = 16;

GameController::GameController() : GameController(DEFAULT_HEIGHT, DEFAULT_WIDTH, DEFAULT_NUMBER_OF_MINES){};

GameController::GameController(int height, int width, int numberOfMines) : grid(Grid({height, width}, numberOfMines))
{
}

GameController::~GameController()
{
}

void GameController::run()
{
    std::cout << "-- Minesweeper --" << std::endl;
    std::cout << "Dimensions: " << this->grid.getDimensions().i << " x " << this->grid.getDimensions().j << std::endl;
    std::cout << "Number of mines: " << this->grid.getNumberOfMines() << std::endl;
}