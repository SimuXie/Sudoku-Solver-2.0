#include "sudoku.h"
#include "sudokuInternal.h"
#include "raymath.h"

bool SudokuTargetIsValid(const Sudoku s) {
    return s->target.x != INVALID && s->target.y != INVALID;
}

void SudokuSetTarget(Sudoku s, int row, int col) {
    s->target.x = col;
    s->target.y = row;
}

void SudokuClearTarget(Sudoku s) {
    s->target.x = INVALID;
    s->target.y = INVALID;
}

bool SudokuHasTarget(const Sudoku s) {
    return SudokuTargetIsValid(s);
}

Vector2 SudokuGetTarget(const Sudoku s) {
    if (!SudokuTargetIsValid(s)) {
        return Vector2Zero();
    }

    return s->target;
}