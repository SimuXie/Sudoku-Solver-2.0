#ifndef SOLVER_H
#define SOLVER_H
#include "sudoku.h"

enum solverType {
    RECURSIVE,
    STEP,
    COUNT
};

/*
Every solver needs the following functions

SOLVE - Solves the sudoku
NEW - Constructor
FREE - Frees memory assigned
INITIATE - Starts the solving
ISACTIVE - Checks if active
ISCOMPLETE - Checks if complete

SOLUTIONS - Gets the current solution count
*/

typedef struct solver *Solver;
void Solve(Solver s);
Solver SolverNew(Sudoku s, const bool shouldCount, enum solverType type);
void SolverFree(Solver s);
void SolverInitiate(Solver s);
bool SolverIsActive(Solver s);
bool SolverIsComplete(Solver s);
int SolverSolutions(Solver s);

// Naive Recursive Solver
typedef struct recursiveSolver *RecursiveSolver;
void RecursiveSolve(RecursiveSolver s);
RecursiveSolver RecursiveSolverNew(Sudoku s, const bool shouldCount);
void RecursiveSolverFree(RecursiveSolver s);
void RecursiveSolverInitiate(RecursiveSolver s);
bool RecursiveSolverIsActive(RecursiveSolver s);
bool RecursiveSolverIsComplete(RecursiveSolver s);
int RecursiveSolverSolutions(RecursiveSolver s);

// Naive Step Solver
typedef struct stepSolver *StepSolver;
void StepSolve(StepSolver s);
StepSolver StepSolverNew(Sudoku sudoku, const bool shouldCount);
void StepSolverFree(StepSolver s);
void StepSolverInitiate(StepSolver s);
bool StepSolverIsActive(StepSolver s);
bool StepSolverIsComplete(StepSolver s);
int StepSolverSolutions(StepSolver s);
#endif