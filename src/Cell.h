#pragma once

struct Cell
{
    bool isMine;
    bool isFlagged;
    bool isRevealed;
    int hintLabel;
};