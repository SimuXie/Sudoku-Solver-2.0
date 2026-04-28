#ifndef SUDOKU_H
#define SUDOKU_H

enum { SUDOKU_SIZE = 81 };

typedef struct sudoku *Sudoku;


Sudoku SudokuNew(void);

void SudokuFreeBoard(Sudoku s);

// DEBUGGERS

void SudokuInputBoard(Sudoku s, int seed[SUDOKU_SIZE]);

void SudokuPrintBoard(Sudoku s);

#endif