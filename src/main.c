#include "raylib.h"

#include "draw.h"
#include "sudoku.h"

#include <stdio.h>

int main(void) {

    Sudoku s = SudokuNew();
    int seed[81] = {
        1, 2, 3, 4, 5, 6, 7, 8, 9,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0,
    };

    SudokuInputBoard(s, seed);
    SudokuPrintBoard(s);


    InitWindow(800, 600, "raylib test");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);        
        DrawFrame(s);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
