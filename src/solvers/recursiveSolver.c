#include "sudoku.h"
#include "mystdlib.h"
#include "stack.h"
#include "constants.h"
#include "raylib.h"
#include "draw.h"
#include "solvers.h"
#include "solversInternal.h"

#include <stdio.h>

#include "raylib.h"

void RecursiveSolver(Sudoku s, int *count, const bool shouldCount) {
    static double lastDrawTime = 0.0;
    const double targetFrameTime = 1.0 / 30.0;   // 30 FPS

    if (*count == 1 && !shouldCount) {
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
        SudokuSetTarget(s, c.x, c.y);
        SudokuSetAnswer(s, c.x, c.y, i);

        double now = GetTime();
        if (now - lastDrawTime >= targetFrameTime) {
            if (WindowShouldClose()) {
                fprintf(stderr, "Exit prompted\n");
                exit(EXIT_FAILURE);
            }
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawFrame(s, *count);
            EndDrawing();

            lastDrawTime = now;
        }

        if (!SudokuIsIllegal(s)) {
            RecursiveSolver(s, count, shouldCount);
        }

        if (*count == 1 && !shouldCount) {
            return;
        }

        SudokuSetAnswer(s, c.x, c.y, 0);
    }
}