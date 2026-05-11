#include "raylib.h"
#include "raymath.h"
#include "draw.h"
#include "sudoku.h"

#include <stdio.h>

#include "constants.h"

static void drawGrid(void);

static void drawDebug(Sudoku s, int count);

static void drawAnswers(Sudoku s);
static void drawPencils(Sudoku s);
static Vector2 getCellPosition(int row, int col);
static void drawPencilInBox(bool *pencils, Vector2 pos);

static void drawHighlight(Sudoku s);
static void drawTarget(Sudoku s);

void DrawFrame(Sudoku s, int count) {
    drawDebug(s, count);

    drawGrid();

    drawHighlight(s);
    drawTarget(s);

    drawAnswers(s);
    drawPencils(s);
}

static void drawDebug(Sudoku s, const int count) {
    int n = 10;

    DrawText("Press ENTER to initiate solver", 10, n, 20, BLACK);
    n += 20;

    // if (SudokuIsIllegal(s)) {
    //     DrawText("Illegal", 10, n, 20, BLACK);
    // }
    // n += 20;
}

static void drawTarget(Sudoku s) {
    if (!SudokuHasTarget(s)) {
        return;
    } 

    Vector2 target = SudokuGetTarget(s);
    Vector2 offset = Vector2Scale(target, BLOCK_SIZE);
    Vector2 start = getCellPosition(0, 0);
    Vector2 targetCell = Vector2Add(start, offset);

    DrawRectangleV(targetCell, (Vector2){BLOCK_SIZE, BLOCK_SIZE}, Fade(TARGET_COLOUR, TARGET_ALPHA));
}

static void drawHighlight(Sudoku s) {
    Vector2 mouse = GetMousePosition();

    Vector2 gridStart = getCellPosition(0, 0);
    int rowChute = INVALID;
    int colChute = INVALID;
    
    for (int i = 0; i < NUM_ROWS; i++) {
        int chuteStart = gridStart.x + BLOCK_SIZE * i;
        int chuteEnd = chuteStart + BLOCK_SIZE;
        if (mouse.x > chuteStart && mouse.x < chuteEnd) {
            rowChute = i;
        }

        chuteStart = gridStart.y + BLOCK_SIZE * i;
        chuteEnd = chuteStart + BLOCK_SIZE;
        if (mouse.y > chuteStart && mouse.y < chuteEnd) {
            colChute = i;
        }
    }

    if (rowChute == INVALID || colChute == INVALID) {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            SudokuClearTarget(s);
        }
        return;
    }
    
    Vector2 highlightOffset = {rowChute * BLOCK_SIZE, colChute * BLOCK_SIZE};
    DrawRectangleV(Vector2Add(gridStart, highlightOffset), (Vector2){BLOCK_SIZE, BLOCK_SIZE}, Fade(HIGHLIGHT_COLOUR, HIGHLIGHT_ALPHA));
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        SudokuSetTarget(s, colChute, rowChute);
    }
}

static void drawAnswers(Sudoku s) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            int ans = SudokuGetAnswer(s, i, j);

            if (ans == 0) {
                continue;
            }

            Vector2 pos = getCellPosition(i, j);

            Vector2 size = MeasureTextEx(GetFontDefault(), TextFormat("%d", ans), TEXT_SIZE, 1);
            pos.x += BLOCK_SIZE / 2 - size.x / 2;
            pos.y += BLOCK_SIZE / 2 - size.y / 2;

            DrawText(TextFormat("%d", ans), pos.x, pos.y, TEXT_SIZE, BLACK);
        }
    }
}

static void drawPencils(Sudoku s) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (SudokuGetAnswer(s, i, j) != 0) {
                continue;
            }

            Vector2 pos = getCellPosition(i, j);
            bool pencils[NUMBERS];
            SudokuGetPencils(s, pencils, i, j);
            drawPencilInBox(pencils, pos);
        }
    }
}

static void drawPencilInBox(bool *pencils, Vector2 pos) {
    for (int i = 0; i < BOX_ROWS; i++) {
        for (int j = 0; j < BOX_COLS; j++) {
            if (pencils[i + j]) {
                DrawText(TextFormat("%d", i + j + 1), pos.x + i * 10, pos.y + j * 10, 10, BLACK);
            }
        }
    }
}

// Gets the top left position of the cell
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