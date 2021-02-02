#include <iostream>
#include "GameController.h"
#include "Grid.h"

const int DEFAULT_HEIGHT = 16;
const int DEFAULT_WIDTH = 16;

GameController::GameController() : GameController(DEFAULT_HEIGHT, DEFAULT_WIDTH){};

GameController::GameController(int height, int width) : grid(Grid({height, width}))
{
}

GameController::~GameController()
{
}

void GameController::run()
{
    std::cout << "Starting Minesweeper" << std::endl;
    std::cout << "Dimensions: " << this->grid.getDimensions().i << " x " << this->grid.getDimensions().j << std::endl;
}