#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mystdlib.h"
#include "sudoku.h"

#define NUMBERS 9

#define NUM_ROWS 9
#define NUM_COLS 9
#define BOX_ROWS 3
#define EMPTY 0

struct cell {
    int ans;
    bool pencil[NUMBERS];
};

struct sudoku {
    struct cell board[NUM_ROWS][NUM_COLS];
};

static void printBorder(void);
static void printDivider(void);

Sudoku SudokuNew(void) {
    struct sudoku *s = myMalloc(sizeof(*s));
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            s->board[i][j].ans = 0;
            for (int k = 0; k < NUMBERS; k++) {
                s->board[i][j].pencil[k] = false;
            }
        }
    }
    
    return s;
}

void SudokuFreeBoard(Sudoku s) {
    free(s);
}

void SudokuInputBoard(Sudoku s, int seed[SUDOKU_SIZE]) {
    int k = 0;
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            s->board[i][j].ans = seed[k++];
        }
    }
}

// Prints the board.
void SudokuPrintBoard(Sudoku s) {
    printBorder();
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            if ((col) % 3 == 0) {
                printf("|");
            } else {
                printf(".");
            }

            if (s->board[row][col].ans == EMPTY) {
                printf("   ");
            } else {
                printf(" %d ", s->board[row][col].ans);
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