#pragma once
#include <GameEntity.h>
#include <vector>
#include <memory>

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

private:
    // Sounds //
    Sound StartSound;
    Sound CreditSound;
    Sound PowerUpSound;
    Sound PacmanDeadSound;
    Sound EnemyDeadSound;

    // GameEntity vectors //
    std::vector<std::shared_ptr<GameEntity>> GameEntities;
    std::vector<std::shared_ptr<GameEntity>> EnemyEntities;

    // Textures //
    Texture WallTexture;
    Texture FoodTexture;

    // Generic functions //
    void ShowScore();
    void StartTimer(Timer &Timer);
    bool eventTriggered(double interval);
    void InitializeCharacter(std::shared_ptr<GameEntity> &Entity, std::vector<std::shared_ptr<GameEntity>> &EntityVector, const float PosX, const float PosY, const char *FilePath, const float Rotation = 0.f, const float Scale = 0.10f);
    void InitializeCharacterVelocity(Character &Character, float DeltaTime);
    void CheckCollisionWithWalls(const std::shared_ptr<GameEntity> &Entity, Character &Character);
    void SetStartingPositions();
    void DefineEnemyAndCellType();
    void AddWallsFoodAndPowerUps();
    void DrawPacmanLives();
    void ShowPacmanUIDesign();

    // Timer reset functions //
    void ResetPowerUp(double time);
    void ResetStartGameDelayTimer(double time);
    void ResetPacmanState(double time);
    void ResetPacman(double time);

    // Pacman //
    void PacmanMove(float DeltaTime);
    void PacmanCollisionWithEnemy(std::vector<std::shared_ptr<GameEntity>> &EnemyEntityVector);
    void SecretDoor();

    // Enemy Related //
    void EnemyController(std::shared_ptr<GameEntity> Entity, Character &Character);
    void BlinkyMove(float DeltaTime);
    void ClydeMove(float DeltaTime);
    void InkyMove(float DeltaTime);
    void PinkyMove(float DeltaTime);

    // Variables //
    int Score = 0;
    int PacmanLives = 3;
    double lastUpdateTime = 0.0;
    bool StartDelay = false;
    bool IsStartGameDelay = true;
    bool IsStartGame = true;
    bool IsPowerUpEnabled = true;
    bool CanAcceptVerticalInput = true;
    bool CanAcceptHorizontalInput = true;
    Directions NextDirection;
};