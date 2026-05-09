#include "sudoku.h"
#include "sudokuInternal.h"

static bool CheckDuplicate(int *masks, int index, int value);

bool SudokuIsFilled(const Sudoku s) {
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {

            if (SudokuGetAnswer(s, row, col) == EMPTY) {
                return false;
            }
        }
    }

    return true;
}

bool SudokuIsIllegal(const Sudoku s) {
    int rows[NUM_ROWS] = {0};
    int cols[NUM_COLS] = {0};
    int boxes[NUM_BOXES] = {0};

    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {

            int value =
                SudokuGetAnswer(s, row, col);

            if (value == EMPTY) {
                continue;
            }

            int box =
                SudokuBoxIndex(row, col);

            if (CheckDuplicate(rows, row, value) ||
                CheckDuplicate(cols, col, value) ||
                CheckDuplicate(boxes, box, value)) {

                return true;
            }
        }
    }

    return false;
}

static bool CheckDuplicate(int *masks, int index, int value) {
    int mask = 1 << value;

    if (masks[index] & mask) {
        return true;
    }

    masks[index] |= mask;

    return false;
}

int SudokuBoxIndex(int row, int col) {
    return (row / 3) * 3 + (col / 3);
}