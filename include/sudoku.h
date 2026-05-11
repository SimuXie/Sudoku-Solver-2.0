#ifndef SUDOKU_H
#define SUDOKU_H

#include <stdbool.h>

#include "raylib.h"
#include "constants.h"

typedef struct sudoku *Sudoku;

/* coding interface */

Sudoku SudokuNew(void);
void SudokuFree(Sudoku s);
Sudoku SudokuDup(Sudoku s);

/* board loading */

void SudokuInputBoard(Sudoku s, const int seed[SUDOKU_SIZE]);

void SudokuFixInitialCells(Sudoku s);

/* answers */

void SudokuSetAnswer(Sudoku s, int row, int col, int value);

int SudokuGetAnswer(const Sudoku s, int row, int col);

void SudokuClearAnswer(Sudoku s, int row, int col);

/* fixed cells */

bool SudokuIsCellFixed(const Sudoku s, int row, int col);

/* pencil marks */

void SudokuAddPencil(Sudoku s, int value);

void SudokuRemovePencil(Sudoku s, int value);

void SudokuClearPencils(Sudoku s, int row, int col);

int SudokuGetPencils(const Sudoku s, bool out[NUMBERS], int row, int col);

/* validation */

bool SudokuIsFilled(const Sudoku s);
bool SudokuIsIllegal(const Sudoku s);

/* targeting */

void SudokuSetTarget(Sudoku s, int row, int col);

void SudokuClearTarget(Sudoku s);

bool SudokuHasTarget(const Sudoku s);

Vector2 SudokuGetTarget(const Sudoku s);

/* debugging */

void SudokuPrintBoard(const Sudoku s);

#endif