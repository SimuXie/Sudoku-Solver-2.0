#include "raylib.h"

#include "draw.h"
#include "sudoku.h"
#include "generator.h"

#include <stdio.h>
#include <time.h>

static void setCursor(void);
static void input(Sudoku s);

int main(void) {

    Sudoku s = SudokuNew();

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

    SudokuInputBoard(s, seed);

    SudokuFixInitialCells(s);

    SudokuPrintBoard(s);

    InitWindow(1200, 800, "raylib sudoku");

    while (!WindowShouldClose()) {

        setCursor();

        if (IsKeyPressed(KEY_ENTER)) {

            int count = 0;

            Solver(s, &count);

            printf("Done!\n");
            printf("Solutions: %d\n", count);
        }

        input(s);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawFrame(s);

        EndDrawing();
    }

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
