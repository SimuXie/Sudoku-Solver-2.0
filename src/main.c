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
    
    SudokuFixSolutions(s);
    
    SudokuPrintBoard(s);
    
    int count = 0;

    clock_t start = clock();
    Solver(s, &count);
    clock_t end = clock();

    double seconds = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Time: %.6f seconds\n", seconds);
}

// int main(void) {

//     Sudoku s = SudokuNew();
//     int seed[81] = {
//     3,0,0, 0,0,0, 4,0,0,
//     0,0,0, 6,0,0, 0,5,0,
//     0,1,0, 0,0,0, 0,0,0,

//     5,0,6, 0,0,0, 0,7,0,
//     8,0,7, 0,0,0, 0,0,0,
//     0,0,0, 0,9,0, 0,0,0,

//     0,0,0, 5,0,8, 0,0,0,
//     0,0,0, 7,0,0, 2,0,0,
//     0,4,0, 0,0,0, 9,0,0
// };

//     // bool pencil[9] = {1};

//     SudokuInputBoard(s, seed);
    
//     SudokuFixSolutions(s);
    
//     SudokuPrintBoard(s);

//     InitWindow(1200, 800, "raylib test");

//     while (!WindowShouldClose()) {
//         setCursor();

//         if (IsKeyPressed(KEY_ENTER)) {
//             int count = 0;
//             Solver(s, &count);
//             printf("Done!\n");
//             printf("Solutions: %d\n", count);
//         }

//         BeginDrawing();
//         ClearBackground(RAYWHITE);        
//         DrawFrame(s);
//         input(s);
//         EndDrawing();
//     }

//     CloseWindow();
//     return 0;
// }

static void input(Sudoku s) {
    if (!SudokuHasTarget(s)) {
        return;
    }

    int input = GetKeyPressed();
    switch (input) {
        case KEY_ONE:
            SudokuAnswer(s, 1);
            break;
        case KEY_TWO:
            SudokuAnswer(s, 2);
            break;
        case KEY_THREE:
            SudokuAnswer(s, 3);
            break;
        case KEY_FOUR:
            SudokuAnswer(s, 4);
            break;
        case KEY_FIVE:
            SudokuAnswer(s, 5);
            break;
        case KEY_SIX:
            SudokuAnswer(s, 6);
            break;
        case KEY_SEVEN:
            SudokuAnswer(s, 7);
            break;
        case KEY_EIGHT:
            SudokuAnswer(s, 8);
            break;
        case KEY_NINE:
            SudokuAnswer(s,9);
            break;
        case KEY_BACKSPACE:
            SudokuAnswer(s, 0);
            break;
    }
}

static void setCursor(void) {
    if (IsCursorHidden()) {
        ShowCursor();
    }
}
