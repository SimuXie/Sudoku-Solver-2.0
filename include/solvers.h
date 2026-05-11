#ifndef SOLVER_H
#define SOLVER_H
#include "sudoku.h"

// Naive Recursive Solver
void RecursiveSolver(Sudoku s, int *count, const bool shouldCount);

// Step Solver
typedef struct stepSolver *StepSolver;
StepSolver SolverNew(Sudoku sudoku);

#endif