#include <stdlib.h>

#include "sudoku.h"
#include "sudokuInternal.h"

static struct cell *GetTargetCell(Sudoku s);

void SudokuAddPencil(Sudoku s, int value) {
    struct cell *cell =
        GetTargetCell(s);

    if (cell == NULL) {
        return;
    }

    cell->pencil[value - 1] = true;
}

void SudokuRemovePencil(Sudoku s, int value) {
    struct cell *cell =
        GetTargetCell(s);

    if (cell == NULL) {
        return;
    }

    cell->pencil[value - 1] = false;
}

void SudokuClearPencils(Sudoku s, int row, int col) {
    struct cell *cell =
        SudokuGetCell(s, row, col);

    for (int i = 0; i < NUMBERS; i++) {
        cell->pencil[i] = false;
    }
}

int SudokuGetPencils(const Sudoku s, bool out[NUMBERS], int row, int col) {
    int count = 0;

    const struct cell *cell =
        SudokuGetCellConst(s, row, col);

    for (int i = 0; i < NUMBERS; i++) {
        out[i] = cell->pencil[i];

        if (out[i]) {
            count++;
        }
    }

    return count;
}

static struct cell *GetTargetCell(Sudoku s) {
    if (!SudokuTargetIsValid(s)) {
        return NULL;
    }

    int row = (int)s->target.y;
    int col = (int)s->target.x;

    return SudokuGetCell(s, row, col);
}