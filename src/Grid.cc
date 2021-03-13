#include <random>
#include <unordered_set>
#include <vector>
#include "Grid.h"

Grid::Grid(Vector2 dimensions, int numberOfMines) : m_dimensions(dimensions), m_numberOfMines(numberOfMines), m_numberOfCellsRevealed(0)
{
    m_cells = std::vector<Cell>(m_dimensions.i * m_dimensions.j);
};

Grid::~Grid(){};

// getCell returns a pointer to the target cell if coordinates are within the grid dimensions, or a pointer to null otherwise.
Cell *Grid::getCell(Vector2 coordinates)
{
    if (coordinates.i >= m_dimensions.i || coordinates.j >= m_dimensions.j)
    {
        return nullptr;
    }
    return &(m_cells[coordinates.i * m_dimensions.j + coordinates.j]);
}

// getAdjacentCoordinates returns a vector of pointers to coordinates that are adjacent to the given coordinates. It takes the Grid limits into account.
std::vector<Vector2> Grid::getAdjacentCoordinates(Vector2 coordinates, bool includeDiagonals)
{
    std::vector<Vector2> adjacentCells = std::vector<Vector2>(3); // 3 is the minimum number of cells to return
    if (coordinates.i == 0)
    {
        // top
        if (coordinates.j == 0)
        {
            // top left
            adjacentCells.push_back(coordinates.right());
            adjacentCells.push_back(coordinates.bottom());
            if (includeDiagonals)
            {
                adjacentCells.push_back(coordinates.bottomRight());
            }
            return adjacentCells;
        }
        else if (coordinates.j == m_dimensions.j - 1)
        {
            // top right
            adjacentCells.push_back(coordinates.left());
            adjacentCells.push_back(coordinates.bottom());
            if (includeDiagonals)
            {
                adjacentCells.push_back(coordinates.bottomLeft());
            }
            return adjacentCells;
        }
        else
        {
            // top middle
            adjacentCells.push_back(coordinates.left());
            adjacentCells.push_back(coordinates.right());
            adjacentCells.push_back(coordinates.bottom());
            if (includeDiagonals)
            {
                adjacentCells.push_back(coordinates.bottomLeft());
                adjacentCells.push_back(coordinates.bottomRight());
            }
            return adjacentCells;
        }
    }
    else if (coordinates.i == m_dimensions.i - 1)
    {
        // bottom
        if (coordinates.j == 0)
        {
            // bottom left
            adjacentCells.push_back(coordinates.top());
            adjacentCells.push_back(coordinates.right());
            if (includeDiagonals)
            {
                adjacentCells.push_back(coordinates.topRight());
            }
            return adjacentCells;
        }
        else if (coordinates.j == m_dimensions.j - 1)
        {
            // bottom right
            adjacentCells.push_back(coordinates.top());
            adjacentCells.push_back(coordinates.left());
            if (includeDiagonals)
            {
                adjacentCells.push_back(coordinates.topLeft());
            }
            return adjacentCells;
        }
        else
        {
            // bottom middle
            adjacentCells.push_back(coordinates.top());
            adjacentCells.push_back(coordinates.left());
            adjacentCells.push_back(coordinates.right());
            if (includeDiagonals)
            {
                adjacentCells.push_back(coordinates.topLeft());
                adjacentCells.push_back(coordinates.topRight());
            }
            return adjacentCells;
        }
    }
    else
    {
        // middle
        if (coordinates.j == 0)
        {
            // middle left
            adjacentCells.push_back(coordinates.top());
            adjacentCells.push_back(coordinates.right());
            adjacentCells.push_back(coordinates.bottom());
            if (includeDiagonals)
            {
                adjacentCells.push_back(coordinates.topRight());
                adjacentCells.push_back(coordinates.bottomRight());
            }
            return adjacentCells;
        }
        else if (coordinates.j == m_dimensions.j - 1)
        {
            // middle right
            adjacentCells.push_back(coordinates.top());
            adjacentCells.push_back(coordinates.left());
            adjacentCells.push_back(coordinates.bottom());
            if (includeDiagonals)
            {
                adjacentCells.push_back(coordinates.topLeft());
                adjacentCells.push_back(coordinates.bottomLeft());
            }
            return adjacentCells;
        }
        else
        {
            // in the middle
            adjacentCells.push_back(coordinates.top());
            adjacentCells.push_back(coordinates.left());
            adjacentCells.push_back(coordinates.right());
            adjacentCells.push_back(coordinates.bottom());
            if (includeDiagonals)
            {
                adjacentCells.push_back(coordinates.topLeft());
                adjacentCells.push_back(coordinates.topRight());
                adjacentCells.push_back(coordinates.bottomLeft());
                adjacentCells.push_back(coordinates.bottomRight());
            }
            return adjacentCells;
        }
    }
}

Vector2 Grid::getDimensions()
{
    return m_dimensions;
}

int Grid::getNumberOfCells()
{
    return m_dimensions.i * m_dimensions.j;
}

int Grid::getNumberOfMines()
{
    return m_numberOfMines;
}

int Grid::getNumberOfEmptyCells()
{
    return getNumberOfCells() - getNumberOfMines();
}

int Grid::getNumberOfRemainingEmptyCells()
{
    return getNumberOfEmptyCells() - m_numberOfCellsRevealed;
}

// initializeMines uses Floyd sample without replacement algorithm to randomly select m_numberOfMines cells and initialize them as mines
void Grid::initializeMines()
{
    std::unordered_set<int> set;
    auto gen = std::mt19937{std::random_device{}()};
    for (int i = m_dimensions.i * m_dimensions.j - m_numberOfMines; i < m_dimensions.i * m_dimensions.j; i++)
    {
        int rdm = std::uniform_int_distribution<>(1, i)(gen);
        if (set.find(rdm) == set.end())
        {
            // rdm is not in the set
            set.insert(rdm);
            m_cells[rdm].isMine = true;
        }
        else
        {
            // rdm is in the set, but i is not because it can be sampled for the first time
            set.insert(i);
            m_cells[i].isMine = true;
        }
    }
}

// processMove evaluates the player move by revealing the target cell and the adjacent cells if relevant
bool Grid::processMove(Vector2 coordinates)
{
    auto cell = getCell(coordinates);
    if (cell->isRevealed)
    {
        // prevent from infinite loop during propagation
        return cell->isMine;
    }
    cell->isRevealed = true;
    m_numberOfCellsRevealed += 1;
    if (cell->isMine)
    {
        return true;
    }
    else
    {
        cell->hintLabel = countAdjacentMines(coordinates);
        if (cell->hintLabel == 0)
        {
            // adjacent cells are revealed, and so on.. until revealing cells that have adjacent mines
            auto adjacentCoordinates = getAdjacentCoordinates(coordinates, false);
            for (auto i = adjacentCoordinates.begin(); i != adjacentCoordinates.end(); ++i)
            {
                processMove(*i);
            }
        }
        return false;
    }
}

int Grid::countAdjacentMines(Vector2 coordinates)
{
    int count = 0;
    auto adjacentCoordinates = getAdjacentCoordinates(coordinates, true);
    for (auto i = adjacentCoordinates.begin(); i != adjacentCoordinates.end(); ++i)
    {
        Cell *cell = getCell(*i);
        if (cell->isMine)
        {
            count++;
        }
    }
    return count;
}