#pragma once
#include <GameEntity.h>
#include <vector>
#include <memory>
#include <bits/stdc++.h>

static const int CELL_ROWS = 25;
static const int CELL_COLS = 25;
static const int CELL_SIZE = 24;

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
    Directions Direction;
    Vector2 Position{0.0, 0.0};
    Vector2 DeathPosition{0.0, 0.0};
    double Speed = 120.0;
    int RouteNumber = 1;
    bool isEaten = false;
    int CurrentFrame = 0;
    int FrameCount = 0;
    int FrameSpeed = 10;
    int ScoreMultiplyer = 0;
};

struct Timer
{
    float LifeTime = 0;
};

// A* pathfinding algorithm //

typedef std::pair<int, int> Pair;
typedef std::pair<double, std::pair<int, int>> pPair;

struct Cell
{
    int Parent_i = 0;
    int Parent_j = 0;
    double f = 0.0;
    double g = 0.0;
    double h = 0.0;
};

class GameLogic
{
public:
    GameLogic();
    ~GameLogic();
    void Render();
    void StartGame();
    void Update();

private:
    // Sounds //
    Sound StartSound;
    Sound CreditSound;
    Sound PowerUpSound;
    Sound PacmanDeadSound;
    Sound PacmanDeadSoundEndPutty;
    Sound EnemyDeadSound;
    Sound RetreatingSound;
    Sound ChaseModeSound;

    // Enemy Colors //
    Color BlinkyColor = RED;
    Color InkyColor = SKYBLUE;
    Color PinkyColor = PINK;
    Color ClydeColor = ORANGE;

    // GameEntity vectors //
    std::vector<std::shared_ptr<GameEntity>> GameEntities;
    std::vector<std::shared_ptr<GameEntity>> EnemyEntities;

    // Pathfinding vectors //
    std::vector<int> BlinkyPathfindingTrailX;
    std::vector<int> BlinkyPathfindingTrailY;

    std::vector<int> ClydePathfindingTrailX;
    std::vector<int> ClydePathfindingTrailY;

    std::vector<int> PinkyPathfindingTrailX;
    std::vector<int> PinkyPathfindingTrailY;

    std::vector<int> InkyPathfindingTrailX;
    std::vector<int> InkyPathfindingTrailY;

    // Patrol vectors //
    std::vector<int> ClydePatrolLocationsX{23, 23, 16, 16};
    std::vector<int> ClydePatrolLocationsY{11, 1, 1, 11};

    std::vector<int> PinkyPatrolLocationsX{1, 8, 8, 1};
    std::vector<int> PinkyPatrolLocationsY{11, 11, 1, 1};

    std::vector<int> BlinkyPatrolLocationsX{1, 1, 8, 8};
    std::vector<int> BlinkyPatrolLocationsY{13, 23, 13, 23};

    std::vector<int> InkyPatrolLocationsX{16, 16, 23, 23};
    std::vector<int> InkyPatrolLocationsY{13, 23, 13, 23};

    // Textures //
    Texture WallTexture;
    Texture FoodTexture;
    Texture GateTexture;
    Texture PacmanDeadTexture;
    Texture GhostEyeTexture;
    Texture PacmanLifeTexture;

    // Generic functions //
    void ShowScore();
    void UpdateEntities(const float &DeltaTime);
    void StartTimer(Timer &Timer);
    bool eventTriggered(double interval);
    void InitCharacter(std::shared_ptr<GameEntity> &Entity, std::vector<std::shared_ptr<GameEntity>> &EntityVector, const float PosX, const float PosY, const char *FilePath, const float Rotation = 0.f, const float WidthScale = 0.08f, const float HeightScale = 0.08f, const int Frames = 1, const float SourceX = 0.f, Color TextureColor = WHITE);
    void SetStartingPositions();
    void DefineEnemyAndCellType();
    void AddWallsFoodAndPowerUps();
    void DrawPacmanLives();
    void ShowPacmanUIDesign();
    void GameOver();
    void CheckPelletCount();
    void SetPowerUpBehaviour(double Frequency, double ResetTime);
    void AddStartGameDelay(double StartDelayAmount);
    void GameMode(double FirstScatteringTime, double FirstChasingTime, double SecondScatteringTime, double SecondChasingTime, double ThirdScatteringTime, double ThirdChasingTime);
    void SetStateScatter();
    void SetStateChase();
    void ResetCharactersStatesAndGameOver();
    void AddLife();

    // Timer reset functions //
    void ResetPowerUp(double time);
    void ResetStartGameDelayTimer(double time);
    void ResetPacmanState(double time);
    void ResetPacman(double time);
    void ChangeToScatterMode(double time);
    void ChangeToChaseMode(double time);

    // Pacman //
    void PacmanMove(const float &DeltaTime);
    void PacmanCollisionWithEnemy(std::vector<std::shared_ptr<GameEntity>> &EnemyEntityVector);
    void SecretDoor();
    void PlayPacmanAnimation();
    void PlayPacmanDeadAnimation();

    // Enemy Related //
    void EnemyMove(const float &DeltaTime, Character &Source, const Character &Destination, std::vector<int> &PathfindingTrailX, std::vector<int> &PathfindingTrailY, std::shared_ptr<GameEntity> &EntityToMove);
    void EnemyMove2StepsAheadPacman(const float &DeltaTime, Character &Source, const Character &Destination, std::vector<int> &PathfindingTrailX, std::vector<int> &PathfindingTrailY, std::shared_ptr<GameEntity> &EntityToMove);
    void BlinkyMove(const float &DeltaTime);
    void ClydeMove(const float &DeltaTime);
    void InkyMove(const float &DeltaTime);
    void PinkyMove(const float &DeltaTime);
    void FallBackToBase(const float &DeltaTime, Character &Source, int PositionX, int PositionY, std::vector<int> &PathfindingTrailX, std::vector<int> &PathfindingTrailY, std::shared_ptr<GameEntity> &EntityToMove);
    void Patrol(const float &DeltaTime, Character &PatrollingCharacter, std::vector<int> &PatrolLocationsX, std::vector<int> &PatrolLocationsY, std::vector<int> &PathfindingTrailX, std::vector<int> &PathfindingTrailY, std::shared_ptr<GameEntity> &EntityToMove);
    void ResetEnemyAndDrawScore(double time, const Timer &EnemyTimer, Character &EnemyCharacter, std::shared_ptr<GameEntity> &EnemyEntity);
    void PlayEnemyAnimation(Character &Source, std::shared_ptr<GameEntity> &EntityToMove);

    // Variables //
    int Score = 0;
    int GhostScore = 400;
    int PelletCount = 0;
    int ChaseScatterRoundCount = 0;
    int NumberOfPellets = 0;
    int PacmanLives = 3;
    double PowerUpTime = 6.0;
    double lastUpdateTime = 0.0;
    bool StartDelay = false;
    bool IsStartGameDelay = true;
    bool IsStartGame = true;
    bool IsPowerUpEnabled = true;
    bool CanAcceptVerticalInput = true;
    bool CanAcceptHorizontalInput = true;
    bool IsLifeAdded = false;
    bool onMobile = false;
    int test = 0;
    Directions NextDirection;

    bool isScatter = true;
    bool isChase = false;
    bool isPowerUpState = false;
    int EatenGhostCount = 0;

    // Animation variables //
    int CurrentFrame = 0;
    int FrameCount = 0;
    int FrameSpeed = 15;

    // Pacman Dead Animation variables //
    int PacmanDeadCurrentFrame = 0;
    int PacmanDeadFrameCount = 60;
    int PacmanDeadFrameSpeed = 3;
    int PacmanDeadFrames = 10;
    float PacmanDeadSourceX = 0.f;

    // A* pathfinding algorithm //
    bool isValid(int row, int col);
    bool isUnBlocked(int grid[CELL_ROWS][CELL_COLS], int row, int col);
    bool isDestination(int row, int col, Pair dest);
    double CalculateHValue(int row, int col, Pair dest);
    void TracePath(Cell CellDetails[CELL_ROWS][CELL_COLS], Pair dest, std::vector<int> &PathfindingTrailX, std::vector<int> &PathfindingTrailY);
    void AStarSearch(int grid[CELL_ROWS][CELL_COLS], Pair src, Pair dest, std::vector<int> &PathfindingTrailX, std::vector<int> &PathfindingTrailY);
};