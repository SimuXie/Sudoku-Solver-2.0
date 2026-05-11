#include "solvers.h"
#include "sudoku.h"

struct cell getNextCell(Sudoku s);

struct cell {
    int x;
    int y;
};