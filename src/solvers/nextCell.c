#include "solvers.h"
#include "solversInternal.h"

struct cell getNextCell(Sudoku s) {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            if (SudokuGetAnswer(s, i, j) == 0) {
                struct cell cell;
                cell.x = i;
                cell.y = j;
                return cell;
            }
        }
    }

    struct cell cell;
    cell.x = -1;
    cell.y = -1;

    return cell;
}
