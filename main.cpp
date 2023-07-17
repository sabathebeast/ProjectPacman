#include <raylib.h>
#include <GameLogic.h>

int main()
{
    InitWindow(840, 840, "PACMAN");
    SetTargetFPS(60);

    GameLogic gameLogic = GameLogic();

    while (!WindowShouldClose())
    {
        float DeltaTime = GetFrameTime();
        BeginDrawing();
        gameLogic.Render();
        ClearBackground(BLACK);

        gameLogic.Update(DeltaTime);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}