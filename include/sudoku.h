#ifndef SUDOKU_H
#define SUDOKU_H

#include "constants.h"

typedef struct sudoku *Sudoku;

/*
-Interface-
*/
Sudoku SudokuNew(void);

void SudokuFreeBoard(Sudoku s);

bool SudokuIsFilled(Sudoku s);

bool SudokuIsIllegal(Sudoku s);

void SudokuFixSolutions(Sudoku s);

bool SudokuIsCellFixed(Sudoku s, int row, int col);

/*
-Writing-
Functions to write to the Sudoku
*/

void SudokuAnswer(Sudoku s, int ans);

void SudokuSetAnswer(Sudoku s, int row, int col, int a);

void SudokuFastPencil(Sudoku s);

/*
-Targetting-
Targets a cell to perform operations like answering, pencilling, or erasing.
*/
// Returns the target. Assumes there is one.
Vector2 SudokuGetTarget(Sudoku s);

// Returns true if there is a currently valid target.
bool SudokuHasTarget(Sudoku s);

// Removes current target.
void SudokuUntarget(Sudoku s);

// Targets input cell.
void SudokuTarget(Sudoku s, int row, int col);

/*
-Answering-
Returns values for cells and answers.
*/
// Returns the answer at a certain cell.
int SudokuGetCellAnswer(Sudoku s, int row, int col);

// Saves the pencils of a board into the input array.
int SudokuGetCellPencils(Sudoku s, bool pencil[NUMBERS], int row, int col);

// DEBUGGERS

void SudokuInputBoard(Sudoku s, int seed[SUDOKU_SIZE]);

void SudokuPrintBoard(Sudoku s);

#endif