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