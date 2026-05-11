// #include "solvers.h"
// #include "solversInternal.h"
// #include "constants.h"
// #include "mystdlib.h"

// #include "stack.h"

// typedef struct stackFrame *Frame;

// struct stackFrame {
//     Sudoku s;
//     struct cell current;
//     int cand;
// };

// struct stepSolver {
//     Stack stack;
    
//     bool complete;
//     int solutions;
// };

// static Frame createFrame(Sudoku s, struct cell c);
// static Frame getFirstFrame(Sudoku sudoku);
// static void freeFrame(Frame f);

// StepSolver SolverNew(Sudoku sudoku) {
//     StepSolver s = myMalloc(sizeof(*s));
//     s->stack = StackNew();
//     StackPush(s, getFirstFrame(sudoku));
//     s->complete = false;
//     s->solutions = 0;
//     return s;
// }

// static Frame getFirstFrame(Sudoku sudoku) {
//     struct cell c = getNextCell(sudoku);
//     Frame f = createFrame(sudoku, c);
//     return f;
// }

// void StepSolverFree(StepSolver s) {
//     while (!StackIsEmpty(s->stack)) {
//         Frame f = StackPop(s->stack);
//         freeFrame(f);
//     }

//     StackFree(s->stack);
//     free(s);
// }

// static void freeFrame(Frame f) {
//     SudokuFree(f->s);
//     free(f);
// }

// void StepSolve(StepSolver s) {
//     if (StackIsEmpty(s->stack)) {
        
//     }
// }

// static Frame createFrame(Sudoku sudoku, struct cell c) {
//     Frame f = myMalloc(sizeof(*f));
//     f->s = SudokuDup(sudoku);
//     f->cand = 0;
//     f->current = c;

//     return f;
// }
