#include "raylib.h"

int main(void) {
    InitWindow(800, 600, "raylib test");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("It works!", 350, 280, 20, BLACK);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}