#include "solvers.h"
#include "solversInternal.h"
#include "constants.h"
#include "mystdlib.h"

#include <stdio.h>

#include "stack.h"

typedef struct stackFrame *Frame;

struct stackFrame {
    Sudoku s;
    struct cell current;
    int lastVisited;
};

struct stepSolver {
    Sudoku sudoku;
    Stack stack;
    
    bool shouldCount;
    bool active;
    bool complete;
    int solutions;
};

static Frame createFrame(Sudoku s, struct cell c);
static Frame getFirstFrame(Sudoku sudoku);
static void freeFrame(Frame f);

void StepSolve(StepSolver s) {
    if (StackIsEmpty(s->stack)) {
        s->complete = true;
        s->active = false;
        return;
    }

    Frame f = StackPeek(s->stack);

    if (SudokuIsFilled(s->sudoku) && !SudokuIsIllegal(s->sudoku)) {
        s->solutions++;
        if (s->shouldCount) {
            printf("Solutions: %d\n", s->solutions);
            SudokuSetAnswer(s->sudoku, f->current.x, f->current.y, 0);
            freeFrame(StackPop(s->stack));
            return;
        }
    }

    f->lastVisited++;
    
    if (f->lastVisited > NUMBERS) {
        SudokuSetAnswer(s->sudoku, f->current.x, f->current.y, 0);
        freeFrame(StackPop(s->stack));
        return;
    }

    SudokuSetAnswer(s->sudoku, f->current.x, f->current.y, f->lastVisited);

    if (SudokuIsIllegal(s->sudoku)) {
        SudokuSetAnswer(s->sudoku, f->current.x, f->current.y, 0);
        return;
    }

    Frame next = createFrame(s->sudoku, getNextCell(s->sudoku));
    StackPush(s->stack, next);
}

StepSolver StepSolverNew(Sudoku sudoku, const bool shouldCount) {
    StepSolver s = myMalloc(sizeof(*s));
    s->sudoku = sudoku;
    s->stack = StackNew();
    StackPush(s->stack, getFirstFrame(sudoku));

    s->shouldCount = shouldCount;
    s->active = false;
    s->complete = false;
    s->solutions = 0;
    return s;
}

void StepSolverInitiate(StepSolver s) {
    s->active = true;
}

bool StepSolverIsActive(StepSolver s) {
    return s->active;
}

bool StepSolverIsComplete(StepSolver s) {
    return s->complete;
}

static Frame getFirstFrame(Sudoku sudoku) {
    struct cell c = getNextCell(sudoku);
    Frame f = createFrame(sudoku, c);
    return f;
}

void StepSolverFree(StepSolver s) {
    while (!StackIsEmpty(s->stack)) {
        Frame f = StackPop(s->stack);
        freeFrame(f);
    }
    StackFree(s->stack);
    free(s);
}

static void freeFrame(Frame f) {
    SudokuFree(f->s);
    free(f);
}

static Frame createFrame(Sudoku sudoku, struct cell c) {
    Frame f = myMalloc(sizeof(*f));
    f->s = SudokuDup(sudoku);
    f->lastVisited = 0;
    f->current = c;

    return f;
}

int StepSolverSolutions(StepSolver s) {
    return s->solutions;
}
