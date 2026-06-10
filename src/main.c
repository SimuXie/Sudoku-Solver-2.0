#include "raylib.h"

#include "draw.h"
#include "sudoku.h"
#include "solvers.h"

#include <stdio.h>
#include <time.h>

static void setCursor(void);
static void input(Sudoku s);

#define RENDER_TIME (0)

int main(void) {

    SetTargetFPS(0);

    Sudoku s = SudokuNew();

    // // EMPTY
    // int seed[81] = {
    //     0,0,0, 0,0,0, 0,0,0,
    //     0,0,0, 0,0,0, 0,0,0,
    //     0,0,0, 0,0,0, 0,0,0,

    //     0,0,0, 0,0,0, 0,0,0,
    //     0,0,0, 0,0,0, 0,0,0,
    //     0,0,0, 0,0,0, 0,0,0,

    //     0,0,0, 0,0,0, 0,0,0,
    //     0,0,0, 0,0,0, 0,0,0,
    //     0,0,0, 0,0,0, 0,0,0
    // };

    // HARD
    int seed[81] = {
        3,0,0, 0,0,0, 4,0,0,
        0,0,0, 6,0,0, 0,5,0,
        0,1,0, 0,0,0, 0,0,0,

        5,0,6, 0,0,0, 0,7,0,
        8,0,7, 0,0,0, 0,0,0,
        0,0,0, 0,9,0, 0,0,0,

        0,0,0, 5,0,8, 0,0,0,
        0,0,0, 7,0,0, 2,0,0,
        0,4,0, 0,0,0, 9,0,0
    };

    // // EASY
    // int seed[81] = {
    //     9,2,8, 4,1,0, 0,0,0,
    //     1,0,6, 7,0,0, 0,0,0,
    //     0,5,7, 2,6,8, 0,0,9,

    //     0,7,5, 3,8,0, 0,0,0,
    //     0,9,1, 6,0,7, 0,0,4,
    //     4,0,2, 9,0,1, 8,6,7,

    //     5,8,9, 0,7,2, 3,4,0,
    //     0,6,4, 8,9,0, 0,5,2,
    //     2,1,0, 5,4,6, 7,0,8
    // };

    SudokuInputBoard(s, seed);

    // SudokuFixInitialCells(s);

    SudokuPrintBoard(s);

    InitWindow(1200, 800, "raylib sudoku");

    Solver solver = SolverNew(s, false, STEP);
    double lastRender = 0;
    double lastTime = 0;

    while (!WindowShouldClose()) {
        setCursor();
        if (IsKeyPressed(KEY_ENTER)) {
            SolverInitiate(solver);
        }

        if (SolverIsActive(solver)) {
            lastTime = GetTime();
            Solve(solver);
        }

        input(s);
        if (GetTime() - lastRender > RENDER_TIME) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawFrame(s, 0);
            EndDrawing();
            lastRender = GetTime();
        }
    }
    SolverFree(solver);
    SudokuFree(s);
    CloseWindow();
    return 0;
}

static void input(Sudoku s) {

    if (!SudokuHasTarget(s)) {
        return;
    }

    Vector2 target = SudokuGetTarget(s);

    int row = (int)target.y;
    int col = (int)target.x;

    int key = GetKeyPressed();

    switch (key) {

        case KEY_ONE:
            SudokuSetAnswer(s, row, col, 1);
            break;

        case KEY_TWO:
            SudokuSetAnswer(s, row, col, 2);
            break;

        case KEY_THREE:
            SudokuSetAnswer(s, row, col, 3);
            break;

        case KEY_FOUR:
            SudokuSetAnswer(s, row, col, 4);
            break;

        case KEY_FIVE:
            SudokuSetAnswer(s, row, col, 5);
            break;

        case KEY_SIX:
            SudokuSetAnswer(s, row, col, 6);
            break;

        case KEY_SEVEN:
            SudokuSetAnswer(s, row, col, 7);
            break;

        case KEY_EIGHT:
            SudokuSetAnswer(s, row, col, 8);
            break;

        case KEY_NINE:
            SudokuSetAnswer(s, row, col, 9);
            break;

        case KEY_BACKSPACE:
            SudokuClearAnswer(s, row, col);
            break;
    }
}

static void setCursor(void) {
    if (IsCursorHidden()) {
        ShowCursor();
    }
}
