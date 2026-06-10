#include "solvers.h"
#include "stdlib.h"
#include "mystdlib.h"

struct solver {
    enum solverType type;

    RecursiveSolver recursive;
    StepSolver step;
};

void Solve(Solver s) {
    switch (s->type) {
        case RECURSIVE:
            RecursiveSolve(s->recursive);
            break;
        case STEP:
            StepSolve(s->step);
            break;
    }
}

Solver SolverNew(Sudoku sudoku, const bool shouldCount, enum solverType type) {
    Solver s = myMalloc(sizeof(*s));
    s->type = type;
    switch (type) {
        case RECURSIVE:
            s->recursive = RecursiveSolverNew(sudoku, shouldCount);
            break;
        case STEP:
            s->step = StepSolverNew(sudoku, shouldCount);
            break;
    }
    return s;
}

void SolverFree(Solver s) {
    switch (s->type) {
        case RECURSIVE:
            RecursiveSolverFree(s->recursive);
            break;
        case STEP:
            StepSolverFree(s->step);
            break;
    }

    free(s);
}

void SolverInitiate(Solver s) {
    switch (s->type) {
        case RECURSIVE:
            RecursiveSolverInitiate(s->recursive);
            break;
        case STEP:
            StepSolverInitiate(s->step);
            break;
    }
}

bool SolverIsActive(Solver s) {
    switch (s->type) {
        case RECURSIVE:
            RecursiveSolverIsActive(s->recursive);
            break;
        case STEP:
            StepSolverIsActive(s->step);
            break;
    }
}

bool SolverIsComplete(Solver s) {
    switch (s->type) {
        case RECURSIVE:
            RecursiveSolverIsComplete(s->recursive);
            break;
        case STEP:
            StepSolverIsComplete(s->step);
            break;
    }
}

int SolverSolutions(Solver s) {
    switch (s->type) {
        case RECURSIVE:
            RecursiveSolverSolutions(s->recursive);
            break;
        case STEP:
            StepSolverSolutions(s->step);
            break;
    }
}