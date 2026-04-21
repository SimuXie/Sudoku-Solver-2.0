#include "raylib.h"
#include "draw.h"

#include <stdio.h>

#define BLOCK_SIZE 50
#define GRID_SIZE 9
#define START_X 100
#define START_Y 100

void DrawFrame(void) {
    for (int i = 0; i < GRID_SIZE + 1; i++) {
        DrawLine(START_X + i * BLOCK_SIZE, START_Y, START_X + i * BLOCK_SIZE, START_Y + GRID_SIZE * BLOCK_SIZE, BLACK);
    }

    for (int i = 0; i < GRID_SIZE + 1; i++) {
        DrawLine(START_X, START_Y + i * BLOCK_SIZE, START_X + GRID_SIZE * BLOCK_SIZE, START_Y + i * BLOCK_SIZE, BLACK);
    }
}