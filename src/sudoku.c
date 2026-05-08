#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "mystdlib.h"
#include "sudoku.h"
#include "raylib.h"
#include "raymath.h"

#include "constants.h"

struct cell {
    int ans;
    bool pencil[NUMBERS];
    bool fixed;
};

struct sudoku {
    struct cell board[NUM_ROWS][NUM_COLS];
    Vector2 target;
};

static bool isValidTarget(Sudoku s);

static bool isInRow(Sudoku s, int row, int ans);
static bool isInCol(Sudoku s, int col, int ans);
static bool isInBox(Sudoku s, int row, int col, int ans);

static void printBorder(void);
static void printDivider(void);

void SudokuFastPencil(Sudoku s) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            for (int k = 0; k < NUMBERS; k++) {
                if (!isInRow(s, i, k + 1) && !isInCol(s, j, k + 1) && !isInBox(s, i, j, k + 1)) {
                    s->board[i][j].pencil[k] = true;
                } 
            }
        }
    }
}

void SudokuSetAnswer(Sudoku s, int row, int col, int a) {
    s->board[row][col].ans = a;
    SudokuFastPencil(s);
}

static bool isInRow(Sudoku s, int row, int ans) {
    for (int i = 0; i < NUM_COLS; i++) {
        if (s->board[row][i].ans == ans) {
            return true;
        }
    }

    return false;
}

static bool isInCol(Sudoku s, int col, int ans) {
    for (int i = 0; i < NUM_ROWS; i++) {
        if (s->board[i][col].ans == ans) {
            return true;
        }
    }

    return false;
}

static bool isInBox(Sudoku s, int row, int col, int ans) {
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (s->board[startRow + i][startCol + j].ans == ans) {
                return true;
            }
        }
    }

    return false;
}

bool SudokuIsFilled(Sudoku s) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (SudokuGetCellAnswer(s, i, j) == 0) {
                return false;
            }
        }
    }

    return true;
}

bool SudokuIsIllegal(Sudoku s) {
    int rows[NUM_ROWS] = {0};
    int cols[NUM_COLS] = {0};
    int boxes[NUM_BOXES] = {0};

    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            int ans = SudokuGetCellAnswer(s, i, j);
            if (ans == 0) {
                continue;
            }

            int mask = 1 << ans;
            int boxIndex = (i / 3) * 3 + (j / 3);

            if (rows[i] & mask) {
                return true;
            }

            if (cols[j] & mask) {
                return true;
            }

            if (boxes[boxIndex] & mask) {
                return true;
            }

            rows[i] |= mask;
            cols[j] |= mask;
            boxes[boxIndex] |= mask;
        }
    }

    return false;
}

int SudokuGetCellPencils(Sudoku s, bool pencil[NUMBERS], int row, int col) {
    int count = 0;
    for (int i = 0; i < NUMBERS; i++) {
        if (s->board[row][col].pencil[i]) {
            count++;
        }
        pencil[i] = s->board[row][col].pencil[i];
    }

    return count;
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
    } else if (SudokuIsCellFixed(s, (int)s->target.y, (int)s->target.x)) {
        return;
    }

    s->board[(int)s->target.y][(int)s->target.x].ans = a;
}

bool SudokuIsCellFixed(Sudoku s, int row, int col) {
    return s->board[row][col].fixed;
}

static bool isValidTarget(Sudoku s) {
    if (s->target.x == INVALID || s->target.y == INVALID) {
        printf("Valid target required\n");
        return false;
    }

    return true;
}

Vector2 SudokuGetTarget(Sudoku s) {
    if (!isValidTarget(s)) {
        return Vector2Zero();
    }

    return s->target;
}

bool SudokuHasTarget(Sudoku s) {
    if (s->target.x == INVALID || s->target.y == INVALID) {
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
            s->board[i][j].fixed = false;
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
Sets input sudoku solutions to be unchangable.
*/
void SudokuFixSolutions(Sudoku s) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (SudokuGetCellAnswer(s, i, j) != 0) {
                s->board[i][j].fixed = true;
            }
        }
    }
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