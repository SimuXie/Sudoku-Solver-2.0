#ifndef SUDOKU_H
#define SUDOKU_H

enum { 
    SUDOKU_SIZE = 81, 
    NUMBERS = 9
};

typedef struct sudoku *Sudoku;


Sudoku SudokuNew(void);

void SudokuFreeBoard(Sudoku s);

// Interface

// Returns the answer at a certain cell.
int SudokuGetCellAnswer(Sudoku s, int row, int col);

// Saves the pencils of a board into the input array.
void SudokuGetCellPencils(Sudoku s, bool pencil[NUMBERS], int row, int col);

// DEBUGGERS

void SudokuInputBoard(Sudoku s, int seed[SUDOKU_SIZE]);

void SudokuPrintBoard(Sudoku s);

#endif