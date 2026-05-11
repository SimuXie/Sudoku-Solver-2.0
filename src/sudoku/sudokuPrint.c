// Debug to print a sudoku board

#include <stdio.h>

#include "sudoku.h"
#include "sudokuInternal.h"

static void printBorder(void);
static void printDivider(void);

void SudokuPrintBoard(const Sudoku s) {
    printBorder();
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            if ((col) % 3 == 0) {
                printf("|");
            } else {
                printf(".");
            }

            int value = SudokuGetAnswer(s, row, col);

            if (value == EMPTY) {
                printf("   ");
            } else {
                printf(" %d ", value);
            }
        }
        printf("|\n");
        if ((row + 1) % BOX_ROWS == 0 && row != NUM_ROWS - 1) {
            printDivider();
        }
    }
    printBorder();
}

// Helper function to print the border.
static void printBorder(void) {
    printf("-------------------------------------\n");
}

// Helper function to print dividers.
static void printDivider(void) {
    printf("|-----------+-----------+-----------|\n");
}