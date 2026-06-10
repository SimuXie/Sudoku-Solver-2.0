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

struct recursiveSolver {
    Sudoku sudoku;

    int solutions;
    bool active;
    bool shouldCount;
    bool complete;
};

void RecursiveSolve(RecursiveSolver s) {
    static double lastDrawTime = 0.0;
    const double targetFrameTime = 1.0 / 30.0;

    if (s->complete) {
        return;
    }

    struct cell c = getNextCell(s->sudoku);

    if (c.x == -1) {

        s->solutions++;

        SudokuPrintBoard(s->sudoku);

        if (!s->shouldCount) {
            s->complete = true;
            s->active = false;
        }

        return;
    }

    for (int i = 1; i <= NUMBERS; i++) {

        SudokuSetTarget(s->sudoku, c.x, c.y);
        SudokuSetAnswer(s->sudoku, c.x, c.y, i);

        double now = GetTime();

        if (now - lastDrawTime >= targetFrameTime) {

            if (WindowShouldClose()) {
                fprintf(stderr, "Exit prompted\n");
                exit(EXIT_FAILURE);
            }

            BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawFrame(s->sudoku, s->solutions);

            EndDrawing();

            lastDrawTime = now;
        }

        if (!SudokuIsIllegal(s->sudoku)) {
            RecursiveSolve(s);
        }

        SudokuSetAnswer(s->sudoku, c.x, c.y, 0);

        if (s->complete) {
            return;
        }
    }
}

RecursiveSolver RecursiveSolverNew(Sudoku s, bool shouldCount) {
    RecursiveSolver solver = myMalloc(sizeof(*solver));

    solver->sudoku = s;

    solver->solutions = 0;
    solver->shouldCount = shouldCount;
    solver->active = false;
    solver->complete = false;

    return solver;
}

void RecursiveSolverFree(RecursiveSolver s) {
    free(s);
}

void RecursiveSolverInitiate(RecursiveSolver s) {
    s->active = true;
}

bool RecursiveSolverIsActive(RecursiveSolver s) {
    return s->active;
}

bool RecursiveSolverIsComplete(RecursiveSolver s) {
    return s->complete;
}

int RecursiveSolverSolutions(RecursiveSolver s) {
    return s->solutions;
}