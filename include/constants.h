#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "raylib.h"

// Code
#define EMPTY 0
#define INVALID -1

#define HIGHLIGHT_COLOUR SKYBLUE
#define HIGHLIGHT_ALPHA 0.5

#define TARGET_COLOUR BLUE
#define TARGET_ALPHA 0.5

// Definitions
#define SUDOKU_SIZE 81
#define NUMBERS 9
#define NUM_ROWS 9
#define NUM_COLS 9
#define NUM_BOXES 9

#define NUM_CHUTES 3
#define BOX_ROWS 3
#define BOX_COLS 3

// Drawing
#define BLOCK_SIZE 50
#define GRID_SIZE 9
#define START_X (GetScreenWidth() / 2) - (NUMBERS/2 * BLOCK_SIZE)
#define START_Y (GetScreenHeight() / 2) - (NUMBERS/2 * BLOCK_SIZE)
#define GRID_SIZE 9

#define TEXT_SIZE 40

#endif