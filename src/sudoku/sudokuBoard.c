#include "sudoku.h"
#include "sudokuInternal.h"

struct cell *SudokuGetCell(Sudoku s, int row, int col) {
    return &s->board[row][col];
}

const struct cell *SudokuGetCellConst(const Sudoku s, int row, int col) {
    return &s->board[row][col];
}

void SudokuSetAnswer(Sudoku s, int row, int col, int value) {
    struct cell *cell = SudokuGetCell(s, row, col);

    if (cell->fixed) {
        return;
    }

    cell->answer = value;
}

int SudokuGetAnswer(const Sudoku s, int row, int col) {
    return SudokuGetCellConst(s, row, col)->answer;
}

void SudokuClearAnswer(Sudoku s, int row, int col) {
    SudokuSetAnswer(s, row, col, EMPTY);
}

bool SudokuIsCellFixed(const Sudoku s, int row, int col) {
    return SudokuGetCellConst(s, row, col)->fixed;
}

void SudokuFixInitialCells(Sudoku s) {
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {

            if (s->board[row][col].answer != EMPTY) {
                s->board[row][col].fixed = true;
            }
        }
    }
}