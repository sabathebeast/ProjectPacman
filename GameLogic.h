#pragma once
#include <vector>
#include <GameEntity.h>
#include <memory>
#include <unordered_map>

enum class Directions : unsigned char
{
    None,
    Up,
    Down,
    Left,
    Right,
    MAX
};

class GameLogic
{
public:
    GameLogic();
    ~GameLogic();
    void Render();
    void StartGame();
    void Update(float DeltaTime);
    int CellRows = 0;
    int CellSize = 0;
    int CellCols = 0;

protected:
private:
    std::vector<Directions> Mover;
    void StartTimer(double seconds);
    Sound StartSound;
    bool IsStartGame = true;
    bool StartDelay = false;
    std::vector<GameEntity *> gameEntities{};

    // Wall Related //
    std::vector<GameEntity *> WallEntities{};
    Vector2 WallPos{};
    Texture WallTexture;

    // Food Related //
    std::vector<GameEntity *> FoodEntities{};
    Vector2 FoodPos{};
    Texture FoodTexture;
    Sound CreditSound;
    int Score = 0;
    float scenario = 0.f;

    // Pacman Related //
    Sound PacmanDeadSound;
    Vector2 PacmanPos{};
    float PacmanSpeed = 100.f;
    float PacmanVelocity = 0.f;
    float PacmanUpVelocity = 0.f;
    float PacmanDownVelocity = 0.f;
    float PacmanRightVelocity = 0.f;
    float PacmanLeftVelocity = 0.f;
    void PacmanMove(float DeltaTime);
    void InitializePacmanVelocity(float DeltaTime);
    void PacmanCollisionCheck();
    void SecretDoor();
    Directions PacmanDirection;

    // Blinky Related //
    Vector2 BlinkyPos{};
    float BlinkySpeed = 60.f;
    float BlinkyUpVelocity = 0.f;
    float BlinkyDownVelocity = 0.f;
    float BlinkyRightVelocity = 0.f;
    float BlinkyLeftVelocity = 0.f;
    void BlinkyMove(float DeltaTime);

    double lastUpdateTime = 0.0;
    bool eventTriggered(double interval);
    void ShowScore();
};