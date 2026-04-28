#include "raylib.h"

#include "draw.h"
#include "sudoku.h"

#include <stdio.h>

int main(void) {

    Sudoku s = SudokuNew();
    int seed[81] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0,
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


    // InitWindow(800, 600, "raylib test");

    // while (!WindowShouldClose()) {
    //     BeginDrawing();
    //     ClearBackground(RAYWHITE);        
    //     DrawFrame();
    //     EndDrawing();
    // }

    // CloseWindow();
    return 0;
}
