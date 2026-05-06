#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mystdlib.h"
#include "sudoku.h"
#include "raylib.h"

#define NUMBERS 9

#define NUM_ROWS 9
#define NUM_COLS 9
#define BOX_ROWS 3
#define EMPTY 0
#define INVALID -1

struct cell {
    int ans;
    bool pencil[NUMBERS];
};

struct sudoku {
    struct cell board[NUM_ROWS][NUM_COLS];
    Vector2 target;
};

static bool isValidTarget(Sudoku s);

static void printBorder(void);
static void printDivider(void);

void SudokuGetCellPencils(Sudoku s, bool pencil[NUMBERS], int row, int col) {
    for (int i = 0; i < NUMBERS; i++) {
        pencil[i] = s->board[row][col].pencil[i];
    }
}

int SudokuGetCellAnswer(Sudoku s, int row, int col) {
    return s->board[row][col].ans;
}

void SudokuPencil(Sudoku s, int a) {
    if (!isValidTarget(s)) {
        return;
    }
    s->board[(int)s->target.x][(int)s->target.y].pencil[a - 1] = true;
}

void SudokuAnswer(Sudoku s, int a) {
    if (!isValidTarget(s)) {
        return;
    }
    s->board[(int)s->target.x][(int)s->target.y].ans = a;
}

static bool isValidTarget(Sudoku s) {
    if (s->target.x == INVALID || s->target.y == INVALID) {
        printf("Valid target required\n");
        return false;
    }

    return true;
}

void SudokuUntarget(Sudoku s) {
    s->target.x = INVALID;
    s->target.y = INVALID;
}

void SudokuTarget(Sudoku s, int row, int col) {
    s->target.x = col;
    s->target.y = row;
}

/*
Creates a new Sudoku board
*/
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

    s->target.x = INVALID;
    s->target.y = INVALID;
    
    return s;
}

/*
Frees memory allocated to a board.
*/
void SudokuFreeBoard(Sudoku s) {
    free(s);
}

/*
Input a custom board based on a size 81 int array.
*/
void SudokuInputBoard(Sudoku s, int seed[SUDOKU_SIZE]) {
    int k = 0;
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            s->board[i][j].ans = seed[k++];
        }
    }
}

// Prints the board into stdout.
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