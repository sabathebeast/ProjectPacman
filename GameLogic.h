#pragma once
#include <vector>
#include <GameEntity.h>
#include <memory>
#include <unordered_map>

enum class Directions
{
    D_None,
    D_Up,
    D_Down,
    D_Left,
    D_Right,
    D_MAX
};

class GameLogic
{
public:
    GameLogic();
    ~GameLogic();
    void Render();
    void StartGame();
    void Update(float DeltaTime);
    int CellRows{};
    int CellSize{};
    int CellCols{};

protected:
private:
    void StartTimer(double seconds);
    Sound StartSound{};
    bool IsStartGame{true};
    bool StartDelay{false};
    std::vector<GameEntity *> gameEntities{};
    GameEntity *Clyde = new GameEntity();
    GameEntity *Inky = new GameEntity();
    GameEntity *Pinky = new GameEntity();

    // Wall Related //
    std::vector<GameEntity *> WallEntities{};
    Vector2 WallPos{};
    Texture WallTexture{};

    // Food Related //
    std::vector<GameEntity *> FoodEntities{};
    Vector2 FoodPos{};
    Texture FoodTexture{};
    Sound CreditSound{};
    int Score{};
    float scenario{};

    // Pacman Related //
    Sound PacmanDeadSound{};
    GameEntity *Pacman = new GameEntity();
    Vector2 PacmanPos{};
    float PacmanSpeed{100};
    float PacmanVelocity{};
    float PacmanUpVelocity{};
    float PacmanDownVelocity{};
    float PacmanRightVelocity{};
    float PacmanLeftVelocity{};
    void PacmanMove(float DeltaTime);
    void InitializePacmanVelocity(float DeltaTime);
    void PacmanCollisionCheck();
    void SecretDoor();
    Directions PacmanDirection{};

    // Blinky Related //
    GameEntity *Blinky = new GameEntity();
    Vector2 BlinkyPos{};
    float BlinkySpeed{60};
    float BlinkyUpVelocity{};
    float BlinkyDownVelocity{};
    float BlinkyRightVelocity{};
    float BlinkyLeftVelocity{};
    void BlinkyMove(float DeltaTime);

    double lastUpdateTime{};
    bool eventTriggered(double interval);
    void ShowScore();
};