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

struct Character
{
    Vector2 Position{0, 0};
    int Speed = 2;
    float UpVelocity = 0.f;
    float DownVelocity = 0.f;
    float RightVelocity = 0.f;
    float LeftVelocity = 0.f;
    Directions Direction;
};

struct Timer
{
    float LifeTime = 0;
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
    Sound StartSound;
    bool IsStartGame = true;
    bool StartDelay = false;
    std::vector<std::shared_ptr<GameEntity>> GameEntities;
    std::vector<std::shared_ptr<GameEntity>> EnemyEntities;

    // Wall Related //
    Texture WallTexture;

    // Food Related //
    Texture FoodTexture;
    Sound CreditSound;
    Sound PowerUpSound;
    int Score = 0;
    float scenario = 0.f;

    // Pacman Related //
    Sound PacmanDeadSound;
    void PacmanMove(float DeltaTime);
    void PacmanCollisionWithEnemy(std::vector<std::shared_ptr<GameEntity>> &EnemyEntityVector);
    void SecretDoor();
    void StartTimer(Timer &Timer);
    void ResetPacmanState(double time);
    void ResetPacman(double time);
    void ResetPowerUp(double time);
    bool IsPowerUpEnabled = true;
    void ResetStartGameDelayTimer(double time);
    bool IsStartGameDelay = true;
    int PacmanLives = 3;
    bool CanAcceptVerticalInput = true;
    bool CanAcceptHorizontalInput = true;
    Directions NextDirection;

    void DrawPacmanLives();
    void ShowPacmanUIDesign();

    // Enemy Related //
    Sound EnemyDeadSound;
    void BlinkyMove(float DeltaTime);
    void ClydeMove(float DeltaTime);
    void InkyMove(float DeltaTime);
    void PinkyMove(float DeltaTime);

    double lastUpdateTime = 0.0;
    bool eventTriggered(double interval);
    void ShowScore();
    void InitializeCharacter(std::shared_ptr<GameEntity> &Entity, std::vector<std::shared_ptr<GameEntity>> &EntityVector, const float PosX, const float PosY, const char *FilePath, const float Rotation = 0.f, const float Scale = 0.1f);
    void InitializeCharacterVelocity(Character &Character, float DeltaTime);
    void CheckCollisionWithWalls(const std::shared_ptr<GameEntity> &Entity, Character &Character);
    void EnemyController(std::shared_ptr<GameEntity> Entity, Character &Character);
    void SetStartingPositions();
    void DefineEnemyAndCellType();
    void AddWallsFoodAndPowerUps();
};