# Minesweeper

A C++ implementation of the famous Minesweeper.

The goal of the game is to identify all mines in a two-dimensional grid.

## How to launch the game

- Run `make` in the root of the repository to build the game
- Launch the game with `./mineseeper`

The game will ask you for the next move in the CLI. Input you answer in two steps:

- First, enter the index of the row (starting at 0)
- Next, entre the index of the column (starting at 0)

You lose if you try to reveal a cell that has a mine.
You win when you have revealed all empty cells, which mean all remaining hidden cells are mines.

## Developing

### Styleguide

https://google.github.io/styleguide/cppguide.html
