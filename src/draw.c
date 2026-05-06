#include "raylib.h"
#include "draw.h"
#include "sudoku.h"

#include <stdio.h>

#define BLOCK_SIZE 50
#define GRID_SIZE 9
#define START_X 100
#define START_Y 100

#define NUM_ROWS 9
#define NUM_COLS 9

static void drawGrid(void);

static void drawAnswers(Sudoku s);
static Vector2 getCellPosition(int row, int col);

void DrawFrame(Sudoku s) {
    drawGrid();
    drawAnswers(s);
}

static void drawAnswers(Sudoku s) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            int ans = SudokuGetCellAnswer(s, i, j);

            if (ans == 0) {
                continue;
            }

            Vector2 pos = getCellPosition(i, j);

            pos.y += 10;
            pos.x += 15;
            DrawText(TextFormat("%d", ans), pos.x, pos.y, 40, BLACK);
        }
    }
}

static Vector2 getCellPosition(int row, int col) {
    Vector2 v;
    v.x = START_X + col * BLOCK_SIZE;
    v.y = START_Y + row * BLOCK_SIZE;

    return v;
}

static void drawGrid(void) {
    for (int i = 0; i < GRID_SIZE + 1; i++) {
        Color colour = GRAY;
        if (i % 3 == 0) {
            colour = BLACK;
        }
        DrawLine(START_X + i * BLOCK_SIZE, START_Y, START_X + i * BLOCK_SIZE, START_Y + GRID_SIZE * BLOCK_SIZE, colour);
    }

    for (int i = 0; i < GRID_SIZE + 1; i++) {
        Color colour = GRAY;
        if (i % 3 == 0) {
            colour = BLACK;
        }
        DrawLine(START_X, START_Y + i * BLOCK_SIZE, START_X + GRID_SIZE * BLOCK_SIZE, START_Y + i * BLOCK_SIZE, colour);
    }
}