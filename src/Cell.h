#pragma once

struct Cell
{
    Cell() : isMine(false), isFlagged(false), isRevealed(false), hintLabel(0){};
    bool isMine;
    bool isFlagged;
    bool isRevealed;
    int hintLabel;
};