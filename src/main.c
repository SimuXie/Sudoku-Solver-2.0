#include "raylib.h"

#include "draw.h"

#include <stdio.h>

int main(void) {
    InitWindow(800, 600, "raylib test");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);        
        DrawFrame();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
