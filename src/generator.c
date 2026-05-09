#include "sudoku.h"
#include "mystdlib.h"
#include "stack.h"
#include "constants.h"
#include "raylib.h"
#include "time.h"

#include <stdio.h>

struct cell {
    int x;
    int y;
};

static struct cell getNextCell(Sudoku s);
static struct cell getBetterNextCell(Sudoku s);

void Solver(Sudoku s, int *count) {
    if (*count == 1) {
        return;
    }

    struct cell c = getNextCell(s);

    if (c.x == -1) {
        *count += 1;
        printf("Solution found so far: %d\n", *count);
        SudokuPrintBoard(s);
        return;
    }

    for (int i = 1; i <= NUMBERS; i++) {

        SudokuSetAnswer(s, c.x, c.y, i);

        if (!SudokuIsIllegal(s)) {
            Solver(s, count);
        }

        SudokuSetAnswer(s, c.x, c.y, 0);
    }
}

static struct cell getNextCell(Sudoku s) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (SudokuGetAnswer(s, i, j) == 0) {
                struct cell cell;
                cell.x = i;
                cell.y = j;
                return cell;
            }
        }
    }

    struct cell cell;
    cell.x = -1;
    cell.y = -1;

    return cell;
}

static struct cell getBetterNextCell(Sudoku s) {
    int fewestPencils = NUMBERS;

    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (SudokuGetAnswer(s, i, j) != 0) {
                continue;
            }
            bool pencils[NUMBERS];
            int count = SudokuGetPencils(s, pencils, i, j);
            if (count < fewestPencils) {
                fewestPencils = count;
            }
        }
    }

    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (SudokuGetAnswer(s, i, j) != 0) {
                continue;
            }

            bool pencils[NUMBERS];
            int count = SudokuGetPencils(s, pencils, i, j);
            if (count == fewestPencils) {
                struct cell c;
                c.x = i;
                c.y = j;
                return c;
            }
        }
    }

    // full case
    struct cell cell;
    cell.x = -1;
    cell.y = -1;

    return cell;
}
