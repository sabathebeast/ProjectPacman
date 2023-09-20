#include <raylib.h>
#include <GameLogic.h>

int main()
{
    InitWindow(600, 624, "PACMAN");

    GameLogic gameLogic = GameLogic();

    while (!WindowShouldClose())
    {
        BeginDrawing();
        gameLogic.Render();
        ClearBackground(BLACK);

        gameLogic.StartGame();

        gameLogic.Update();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}