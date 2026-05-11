#ifndef SUDOKU_INTERNAL_H
#define SUDOKU_INTERNAL_H

#include <stdbool.h>

#include "raylib.h"
#include "constants.h"
#include "sudoku.h"

struct cell {
    int answer;
    bool pencil[NUMBERS];
    bool fixed;
};

struct sudoku {
    struct cell board[NUM_ROWS][NUM_COLS];
    Vector2 target;
};

/* validation helpers */

bool SudokuTargetIsValid(const Sudoku s);

int SudokuBoxIndex(int row, int col);

/* cell helpers */

struct cell *SudokuGetCell(Sudoku s, int row, int col);

const struct cell *SudokuGetCellConst(const Sudoku s, int row, int col);

#endif