#include <stdlib.h>
#include <string.h>

#include "mystdlib.h"

#include "sudoku.h"
#include "sudokuInternal.h"

static void initialiseCell(struct cell *cell);

Sudoku SudokuNew(void) {
    Sudoku s = myMalloc(sizeof(*s));

    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            initialiseCell(&s->board[row][col]);
        }
    }

    s->target.x = INVALID;
    s->target.y = INVALID;

    return s;
}

static void initialiseCell(struct cell *cell) {
    cell->answer = EMPTY;
    cell->fixed = false;

    for (int i = 0; i < NUMBERS; i++) {
        cell->pencil[i] = false;
    }
}

Sudoku SudokuDup(Sudoku s) {
    Sudoku new = SudokuNew();
    memcpy(new, s, sizeof(*s));
    return new;
}


void SudokuFree(Sudoku s) {
    free(s);
}

void SudokuInputBoard(Sudoku s, const int seed[SUDOKU_SIZE]) {
    int k = 0;

    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            s->board[row][col].answer = seed[k++];
        }
    }
}