#include "GameLogic.h"
#include <GameEntity.h>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <iostream>
#include <cmath>

static const int CELL_ROWS = 20;
static const int CELL_COLS = 21;
static const int CELL_SIZE = 40;

int MazeMap[CELL_ROWS][CELL_COLS] =
    {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1,
        1, 2, 2, 2, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 2, 2, 2, 1,
        1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1,
        1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1,
        1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 2, 2, 2, 1, 0, 0, 0, 1, 2, 2, 2, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 1, 2, 1, 0, 0, 0, 1, 2, 1, 2, 2, 2, 2, 2, 2,
        1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1,
        1, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 1,
        1, 1, 2, 1, 1, 2, 1, 2, 1, 2, 5, 2, 1, 2, 1, 2, 1, 1, 2, 1, 1,
        1, 2, 2, 2, 3, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 3, 2, 2, 2, 1,
        1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

Character PacmanCharacter;
Character BlinkyCharacter;
Character ClydeCharacter;
Character InkyCharacter;
Character PinkyCharacter;

Timer PacmanStateTimer;
Timer PacmanTimer;
Timer PowerUpTimer;
Timer StartGameDelayTimer;

std::shared_ptr<GameEntity> Pacman = std::make_shared<GameEntity>("Pacman");
std::shared_ptr<GameEntity> Blinky = std::make_shared<GameEntity>("Blinky");
std::shared_ptr<GameEntity> Clyde = std::make_shared<GameEntity>("Clyde");
std::shared_ptr<GameEntity> Inky = std::make_shared<GameEntity>("Inky");
std::shared_ptr<GameEntity> Pinky = std::make_shared<GameEntity>("Pinky");

GameLogic::GameLogic()
{
    AddWallsFoodAndPowerUps();

    SetStartingPositions();

    InitializeCharacter(Pacman, EnemyEntities, PacmanCharacter.Position.x, PacmanCharacter.Position.y, "./Assets/Pacman.png", 270.f, 0.065f);
    InitializeCharacter(Blinky, EnemyEntities, BlinkyCharacter.Position.x, BlinkyCharacter.Position.y, "./Assets/Blinky.png");
    InitializeCharacter(Clyde, EnemyEntities, ClydeCharacter.Position.x, ClydeCharacter.Position.y, "./Assets/Clyde.png");
    InitializeCharacter(Inky, EnemyEntities, InkyCharacter.Position.x, InkyCharacter.Position.y, "./Assets/Inky.png");
    InitializeCharacter(Pinky, EnemyEntities, PinkyCharacter.Position.x, PinkyCharacter.Position.y, "./Assets/Pinky.png");

    DefineEnemyAndCellType();

    StartTimer(StartGameDelayTimer);

    InitAudioDevice();
    CreditSound = LoadSound("./Sounds/credit.wav");
    StartSound = LoadSound("./Sounds/game_start.wav");
    PacmanDeadSound = LoadSound("./Sounds/death_1.wav");
    PowerUpSound = LoadSound("./Sounds/power_pellet.wav");
    EnemyDeadSound = LoadSound("./Sounds/eat_ghost.wav");
}

GameLogic::~GameLogic()
{
    UnloadSound(CreditSound);
    UnloadSound(StartSound);
    UnloadSound(PacmanDeadSound);
    UnloadSound(PowerUpSound);
    UnloadSound(EnemyDeadSound);
    CloseAudioDevice();
    UnloadTexture(WallTexture);
    UnloadTexture(FoodTexture);
}

void GameLogic::Render()
{

    for (int i = 0; i < (int)GameEntities.size(); i++)
    {
        if (GameEntities[i]->CellType == CellType::Food)
        {
            Rectangle PacmanRec = {Pacman->GetPosition().x - Pacman->GetTexture().width * Pacman->GetScale() / 2, Pacman->GetPosition().y - Pacman->GetTexture().height * Pacman->GetScale() / 2, Pacman->GetTexture().width * Pacman->GetScale(), Pacman->GetTexture().height * Pacman->GetScale()};
            Rectangle FoodRec = {GameEntities[i]->GetPosition().x - GameEntities[i]->GetTexture().width * GameEntities[i]->GetScale() / 2, GameEntities[i]->GetPosition().y - GameEntities[i]->GetTexture().height * GameEntities[i]->GetScale() / 2, GameEntities[i]->GetTexture().width * GameEntities[i]->GetScale(), GameEntities[i]->GetTexture().height * GameEntities[i]->GetScale()};

            if (CheckCollisionRecs(PacmanRec, FoodRec))
            {
                if (GameEntities[i]->EntityType == EntityType::PowerUp)
                {
                    Score += 100;
                    PlaySound(PowerUpSound);
                    Pacman->State = State::PowerUp;
                    StartTimer(PacmanStateTimer);
                    for (int j = 0; j < (int)GameEntities.size(); j++)
                    {
                        if (GameEntities[j]->CellType == CellType::Enemy)
                        {
                            GameEntities[j]->SetTextureColor(BLUE);
                        }
                    }
                }
                else
                {
                    Score++;
                    PlaySound(CreditSound);
                }
                GameEntities.erase(GameEntities.begin() + i);
            }
        }

        if (GameEntities[i]->EntityType == EntityType::PowerUp)
        {
            if (IsPowerUpEnabled)
            {
                GameEntities[i]->Render();
            }
        }
        else
        {
            GameEntities[i]->Render();
        }
    }
}

void GameLogic::StartGame()
{
    if (IsStartGame)
    {
        PlaySound(StartSound);
        IsStartGame = false;
    }
}

void GameLogic::Update(float DeltaTime)
{
    if (IsStartGameDelay)
    {
        ResetStartGameDelayTimer(5.0);
    }
    if (eventTriggered(0.5))
    {
        StartTimer(PowerUpTimer);
        IsPowerUpEnabled = false;
    }
    if (Pacman->State == State::PowerUp)
    {

        ResetPacmanState(2.2);
    }

    if (!StartDelay && !IsStartGameDelay)
    {
        if (!Pacman->IsDead)
        {
            PacmanMove(DeltaTime);
            BlinkyMove(DeltaTime);
            ClydeMove(DeltaTime);
            InkyMove(DeltaTime);
            PinkyMove(DeltaTime);
        }
    }

    if (StartDelay)
    {
        if (PacmanLives > 0)
        {
            ResetPacman(3.0);
        }
        else
        {
            Pacman->IsDead = true;
            int GameOverTexTSize = MeasureText("GAME OVER!", 100);
            DrawText("GAME OVER!", GetScreenWidth() / 2 - GameOverTexTSize / 2, GetScreenHeight() / 2 - 50, 100, RED);
        }
    }

    if (!IsPowerUpEnabled)
    {
        ResetPowerUp(0.3);
    }

    ShowPacmanUIDesign();
    ShowScore();
    DrawPacmanLives();
}

void GameLogic::StartTimer(Timer &Timer)
{
    Timer.LifeTime = GetTime();
}

void GameLogic::ResetPacman(double time)
{
    double currentTime = GetTime();
    if (currentTime >= PacmanTimer.LifeTime + time)
    {
        NextDirection = Directions::None;
        PacmanCharacter.Direction = Directions::None;
        StartDelay = false;
        SetStartingPositions();
        Pacman->SetPosition(PacmanCharacter.Position.x, PacmanCharacter.Position.y);
        Pacman->SetRotation(270.f);
        PacmanLives--;
    }
}

void GameLogic::ResetPacmanState(double time)
{
    double currentTime = GetTime();
    if (currentTime <= PacmanStateTimer.LifeTime + time)
    {
        Pacman->SetTextureColor(RED);
        Pacman->State = State::PowerUp;
        PacmanCharacter.Speed = 4;
    }
    else
    {
        Pacman->SetTextureColor(YELLOW);
        Pacman->State = State::Nothing;
        PacmanCharacter.Speed = 2;
        for (int j = 0; j < (int)GameEntities.size(); j++)
        {
            if (GameEntities[j]->CellType == CellType::Enemy)
            {
                GameEntities[j]->SetTextureColor(WHITE);
            }
        }
    }
}

void GameLogic::ResetPowerUp(double time)
{
    double currentTime = GetTime();
    if (currentTime >= PowerUpTimer.LifeTime + time)
    {
        IsPowerUpEnabled = true;
    }
}

void GameLogic::ResetStartGameDelayTimer(double time)
{
    double currentTime = GetTime();
    if (currentTime >= StartGameDelayTimer.LifeTime + time)
    {
        IsStartGameDelay = false;
    }
}

void GameLogic::ShowPacmanUIDesign()
{
    DrawText("PAC", 20, 292, 60, YELLOW);
    DrawText("MAN", GetScreenWidth() - 140, 292, 60, YELLOW);
}

bool GameLogic::eventTriggered(double interval)
{
    double currentTime = GetTime();
    if (currentTime - lastUpdateTime >= interval)
    {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

void GameLogic::ShowScore()
{
    const char *ScoreText = "Score:";
    int ScoreTextSize = MeasureText(ScoreText, 20);
    DrawText(ScoreText, 10, GetScreenHeight() - 30, 20, WHITE);
    DrawText(TextFormat("%i", Score), 20 + ScoreTextSize, GetScreenHeight() - 30, 20, WHITE);
}

void GameLogic::CheckCollisionWithWalls(const std::shared_ptr<GameEntity> &Entity, Character &Character)
{
    for (int i = 0; i < (int)GameEntities.size(); i++)
    {
        if (GameEntities[i]->CellType == CellType::Wall)
        {
            if (CheckCollisionPointLine({Entity->GetPosition().x, Entity->GetPosition().y - Entity->GetTexture().height * Entity->GetScale() / 2}, {GameEntities[i]->GetPosition().x - GameEntities[i]->GetTexture().width * GameEntities[i]->GetScale() / 2 - Entity->GetTexture().width * Entity->GetScale() / 2 + 1, GameEntities[i]->GetPosition().y + GameEntities[i]->GetTexture().height * GameEntities[i]->GetScale() / 2}, {GameEntities[i]->GetPosition().x + GameEntities[i]->GetTexture().width * GameEntities[i]->GetScale() / 2 + Entity->GetTexture().width * Entity->GetScale() / 2 - 1, GameEntities[i]->GetPosition().y + GameEntities[i]->GetTexture().height * GameEntities[i]->GetScale() / 2}, 1))
            {
                Character.UpVelocity = 0.f;
            }
            if (CheckCollisionPointLine({Entity->GetPosition().x, Entity->GetPosition().y + Entity->GetTexture().height * Entity->GetScale() / 2}, {GameEntities[i]->GetPosition().x - GameEntities[i]->GetTexture().width * GameEntities[i]->GetScale() / 2 - Entity->GetTexture().width * Entity->GetScale() / 2 + 1, GameEntities[i]->GetPosition().y - GameEntities[i]->GetTexture().height * GameEntities[i]->GetScale() / 2}, {GameEntities[i]->GetPosition().x + GameEntities[i]->GetTexture().width * GameEntities[i]->GetScale() / 2 + Entity->GetTexture().width * Entity->GetScale() / 2 - 1, GameEntities[i]->GetPosition().y - GameEntities[i]->GetTexture().height * GameEntities[i]->GetScale() / 2}, 1))
            {
                Character.DownVelocity = 0.f;
            }
            if (CheckCollisionPointLine({Entity->GetPosition().x + Entity->GetTexture().width * Entity->GetScale() / 2, Entity->GetPosition().y}, {GameEntities[i]->GetPosition().x - GameEntities[i]->GetTexture().width * GameEntities[i]->GetScale() / 2, GameEntities[i]->GetPosition().y - GameEntities[i]->GetTexture().height * GameEntities[i]->GetScale() / 2 - Entity->GetTexture().height * Entity->GetScale() / 2 + 1}, {GameEntities[i]->GetPosition().x - GameEntities[i]->GetTexture().width * GameEntities[i]->GetScale() / 2, GameEntities[i]->GetPosition().y + GameEntities[i]->GetTexture().height * GameEntities[i]->GetScale() / 2 + Entity->GetTexture().height * Entity->GetScale() / 2 - 1}, 1))
            {
                Character.RightVelocity = 0.f;
            }
            if (CheckCollisionPointLine({Entity->GetPosition().x - Entity->GetTexture().width * Entity->GetScale() / 2, Entity->GetPosition().y}, {GameEntities[i]->GetPosition().x + GameEntities[i]->GetTexture().width * GameEntities[i]->GetScale() / 2, GameEntities[i]->GetPosition().y - GameEntities[i]->GetTexture().height * GameEntities[i]->GetScale() / 2 - Entity->GetTexture().height * Entity->GetScale() / 2 + 1}, {GameEntities[i]->GetPosition().x + GameEntities[i]->GetTexture().width * GameEntities[i]->GetScale() / 2, GameEntities[i]->GetPosition().y + GameEntities[i]->GetTexture().height * GameEntities[i]->GetScale() / 2 + Entity->GetTexture().height * Entity->GetScale() / 2 - 1}, 1))
            {
                Character.LeftVelocity = 0.f;
            }
        }
    }
}

void GameLogic::InitializeCharacterVelocity(Character &Character, float DeltaTime)
{
    Character.UpVelocity = DeltaTime * Character.Speed;
    Character.DownVelocity = DeltaTime * Character.Speed;
    Character.LeftVelocity = DeltaTime * Character.Speed;
    Character.RightVelocity = DeltaTime * Character.Speed;
}

void GameLogic::PacmanCollisionWithEnemy(std::vector<std::shared_ptr<GameEntity>> &EnemyEntityVector)
{
    for (int i = 0; i < (int)EnemyEntityVector.size(); i++)
    {
        if (EnemyEntityVector[i]->CellType == CellType::Pacman)
            continue;
        Rectangle PacmanRec = {Pacman->GetPosition().x - Pacman->GetTexture().width * Pacman->GetScale() / 2, Pacman->GetPosition().y - Pacman->GetTexture().height * Pacman->GetScale() / 2, Pacman->GetTexture().width * Pacman->GetScale(), Pacman->GetTexture().height * Pacman->GetScale()};
        Rectangle EnemyRec = {EnemyEntityVector[i]->GetPosition().x - EnemyEntityVector[i]->GetTexture().width * EnemyEntityVector[i]->GetScale() / 2, EnemyEntityVector[i]->GetPosition().y - EnemyEntityVector[i]->GetTexture().height * EnemyEntityVector[i]->GetScale() / 2, EnemyEntityVector[i]->GetTexture().width * EnemyEntityVector[i]->GetScale(), EnemyEntityVector[i]->GetTexture().height * EnemyEntityVector[i]->GetScale()};
        if (CheckCollisionRecs(PacmanRec, EnemyRec))
        {
            if (Pacman->State == State::Nothing)
            {
                StartTimer(PacmanTimer);
                StartDelay = true;
                PlaySound(PacmanDeadSound);
            }
            else
            {
                switch (EnemyEntityVector[i]->EnemyType)
                {
                case Enemy::Blinky:
                    BlinkyCharacter.Position = {400.f, 400.f};
                    break;
                case Enemy::Clyde:
                    ClydeCharacter.Position = {400.f, 400.f};
                    break;
                case Enemy::Inky:
                    InkyCharacter.Position = {400.f, 400.f};
                    break;
                case Enemy::Pinky:
                    PinkyCharacter.Position = {400.f, 400.f};
                    break;
                default:
                    break;
                }
                PlaySound(EnemyDeadSound);
                Score += 1000;
            }
        }
    }
}

void GameLogic::PacmanMove(float DeltaTime)
{
    int PacmanHalfSize = CELL_SIZE / 2;
    int NewPacmanX = PacmanCharacter.Position.x;
    int NewPacmanY = PacmanCharacter.Position.y;

    switch ((GetKeyPressed()))
    {
    case KEY_W:
        NextDirection = Directions::Up;
        break;
    case KEY_S:
        NextDirection = Directions::Down;
        break;
    case KEY_A:
        NextDirection = Directions::Left;
        break;
    case KEY_D:
        NextDirection = Directions::Right;
        break;
    default:
        break;
    }

    if ((NewPacmanX + CELL_SIZE / 2) % CELL_SIZE != 0)
    {
        CanAcceptVerticalInput = false;
    }
    else
    {
        CanAcceptVerticalInput = true;
    }

    if ((NewPacmanY + CELL_SIZE / 2) % CELL_SIZE != 0)
    {
        CanAcceptHorizontalInput = false;
    }
    else
    {
        CanAcceptHorizontalInput = true;
    }

    switch (NextDirection)
    {
    case Directions::Up:
        if (CanAcceptVerticalInput && MazeMap[std::lrint(((NewPacmanY - PacmanHalfSize - PacmanCharacter.Speed) / CELL_SIZE))][std::lrint((NewPacmanX - PacmanHalfSize) / CELL_SIZE)] != 1)
        {
            PacmanCharacter.Direction = NextDirection;
        }
        break;
    case Directions::Down:
        if (CanAcceptVerticalInput && MazeMap[std::lrint((NewPacmanY + PacmanHalfSize) / CELL_SIZE)][std::lrint((NewPacmanX - PacmanHalfSize) / CELL_SIZE)] != 1)
        {
            PacmanCharacter.Direction = NextDirection;
        }
        break;
    case Directions::Left:
        if (CanAcceptHorizontalInput && MazeMap[std::lrint(((NewPacmanY + PacmanHalfSize) / CELL_SIZE)) - 1][std::lrint((NewPacmanX - PacmanHalfSize - PacmanCharacter.Speed) / CELL_SIZE)] != 1)
        {
            PacmanCharacter.Direction = NextDirection;
        }
        break;
    case Directions::Right:
        if (CanAcceptHorizontalInput && MazeMap[std::lrint(((NewPacmanY + PacmanHalfSize) / CELL_SIZE)) - 1][std::lrint((NewPacmanX + PacmanHalfSize) / CELL_SIZE)] != 1)
        {
            PacmanCharacter.Direction = NextDirection;
        }
        break;
    default:
        break;
    }

    if (PacmanCharacter.Direction == Directions::Up)
    {
        auto Y = std::lrint(((NewPacmanY - PacmanHalfSize - PacmanCharacter.Speed) / CELL_SIZE));
        auto X = std::lrint((NewPacmanX - PacmanHalfSize) / CELL_SIZE);

        if (MazeMap[Y][X] != 1)
        {
            Pacman->SetRotation(270.f);
            NewPacmanY -= PacmanCharacter.Speed;
            PacmanCharacter.Position.y = NewPacmanY;
        }
    }

    if (PacmanCharacter.Direction == Directions::Down)
    {
        auto Y = std::lrint((NewPacmanY + PacmanHalfSize) / CELL_SIZE);
        auto X = std::lrint((NewPacmanX - PacmanHalfSize) / CELL_SIZE);

        if (MazeMap[Y][X] != 1)
        {
            Pacman->SetRotation(90.f);
            NewPacmanY += PacmanCharacter.Speed;
            PacmanCharacter.Position.y = NewPacmanY;
        }
    }

    if (PacmanCharacter.Direction == Directions::Left)
    {
        auto Y = std::lrint(((NewPacmanY + PacmanHalfSize) / CELL_SIZE)) - 1;
        auto X = std::lrint((NewPacmanX - PacmanHalfSize - PacmanCharacter.Speed) / CELL_SIZE);

        if (MazeMap[Y][X] != 1)
        {
            Pacman->SetRotation(180.f);
            NewPacmanX -= PacmanCharacter.Speed;
            PacmanCharacter.Position.x = NewPacmanX;
        }
    }

    if (PacmanCharacter.Direction == Directions::Right)
    {
        auto Y = std::lrint(((NewPacmanY + PacmanHalfSize) / CELL_SIZE)) - 1;
        auto X = std::lrint((NewPacmanX + PacmanHalfSize) / CELL_SIZE);

        if (MazeMap[Y][X] != 1)
        {
            Pacman->SetRotation(0.f);
            NewPacmanX += PacmanCharacter.Speed;
            PacmanCharacter.Position.x = NewPacmanX;
        }
    }
    Pacman->SetPosition(PacmanCharacter.Position.x, PacmanCharacter.Position.y);
    DrawText(TextFormat("%i", NewPacmanY), GetScreenWidth() - 100, GetScreenHeight() - 30, 20, WHITE);
    DrawText(TextFormat("%i", NewPacmanX), GetScreenWidth() - 200, GetScreenHeight() - 30, 20, WHITE);

    PacmanCollisionWithEnemy(EnemyEntities);
    SecretDoor(); // REDO
}

void GameLogic::SecretDoor() // REDO
{
    if (Pacman->GetPosition().x + Pacman->GetTexture().width * Pacman->GetScale() / 2 >= GetScreenWidth() && Pacman->GetPosition().y >= 400.f)
    {
        PacmanCharacter.Position.x = 0.f + Pacman->GetTexture().width * Pacman->GetScale() / 2;
        PacmanCharacter.Position.x += PacmanCharacter.RightVelocity;
        Pacman->SetPosition(PacmanCharacter.Position.x, Pacman->GetPosition().y);
    }
    if (Pacman->GetPosition().x - Pacman->GetTexture().width * Pacman->GetScale() / 2 <= 0 && Pacman->GetPosition().y >= 400.f)
    {
        PacmanCharacter.Position.x = GetScreenWidth() - Pacman->GetTexture().width * Pacman->GetScale() / 2 - 2;
        PacmanCharacter.Position.x += PacmanCharacter.LeftVelocity;
        Pacman->SetPosition(PacmanCharacter.Position.x, Pacman->GetPosition().y);
    }
}

void GameLogic::DrawPacmanLives()
{
    for (int i = 0; i < PacmanLives; i++)
    {
        int Offset{30};
        DrawTextureEx(Pacman->GetTexture(), {GetScreenWidth() / 2.0f - 45 + i * Offset, GetScreenHeight() - 33.0f}, 0.f, Pacman->GetScale() / 1.5f, WHITE);
    }
}

void GameLogic::BlinkyMove(float DeltaTime)
{
    InitializeCharacterVelocity(BlinkyCharacter, DeltaTime);
    CheckCollisionWithWalls(Blinky, BlinkyCharacter);
    EnemyController(Blinky, BlinkyCharacter);
}

void GameLogic::ClydeMove(float DeltaTime)
{
    InitializeCharacterVelocity(ClydeCharacter, DeltaTime);
    CheckCollisionWithWalls(Clyde, ClydeCharacter);
    EnemyController(Clyde, ClydeCharacter);
}

void GameLogic::DefineEnemyAndCellType()
{
    Pacman->CellType = CellType::Pacman;
    Pacman->State = State::Nothing;

    Blinky->EnemyType = Enemy::Blinky;
    Blinky->CellType = CellType::Enemy;
    Clyde->EnemyType = Enemy::Clyde;
    Clyde->CellType = CellType::Enemy;
    Inky->EnemyType = Enemy::Inky;
    Inky->CellType = CellType::Enemy;
    Pinky->EnemyType = Enemy::Pinky;
    Pinky->CellType = CellType::Enemy;
}

void GameLogic::AddWallsFoodAndPowerUps()
{
    WallTexture = LoadTexture("./Assets/Wall.png");
    FoodTexture = LoadTexture("./Assets/Food.png");

    for (int i = 0; i < CELL_ROWS; i++)
    {
        for (int j = 0; j < CELL_COLS; j++)
        {
            if (MazeMap[i][j] == 1)
            {
                std::shared_ptr<GameEntity> Wall = std::make_shared<GameEntity>("Wall" + std::to_string(i));
                Wall->AddPositionComponent();
                Wall->AddSprite2DComponentWithTexture(WallTexture);
                Wall->SetPosition(j * CELL_SIZE + CELL_SIZE / 2, i * CELL_SIZE + CELL_SIZE / 2);
                Wall->SetScale(0.085f);
                Wall->CellType = CellType::Wall;
                GameEntities.emplace_back(Wall);
            }
            else if (MazeMap[i][j] == 2)
            {
                std::shared_ptr<GameEntity> Food = std::make_shared<GameEntity>("Food" + std::to_string(i));
                Food->AddPositionComponent();
                Food->AddSprite2DComponentWithTexture(FoodTexture);
                Food->SetPosition(j * CELL_SIZE + CELL_SIZE / 2, i * CELL_SIZE + CELL_SIZE / 2);
                Food->SetScale(0.5f);
                Food->CellType = CellType::Food;
                Food->SetTextureColor(ORANGE);
                GameEntities.emplace_back(Food);
            }
            else if (MazeMap[i][j] == 3)
            {
                std::shared_ptr<GameEntity> PowerUp = std::make_shared<GameEntity>("PowerUp" + std::to_string(i));
                PowerUp->AddPositionComponent();
                PowerUp->AddSprite2DComponentWithTexture(FoodTexture);
                PowerUp->SetPosition(j * CELL_SIZE + CELL_SIZE / 2, i * CELL_SIZE + CELL_SIZE / 2);
                PowerUp->SetScale(1.0f);
                PowerUp->CellType = CellType::Food;
                PowerUp->EntityType = EntityType::PowerUp;
                PowerUp->SetTextureColor(RED);
                GameEntities.emplace_back(PowerUp);
            }
        }
    }
}

void GameLogic::InkyMove(float DeltaTime)
{
    InitializeCharacterVelocity(InkyCharacter, DeltaTime);
    CheckCollisionWithWalls(Inky, InkyCharacter);
    EnemyController(Inky, InkyCharacter);
}

void GameLogic::PinkyMove(float DeltaTime)
{
    InitializeCharacterVelocity(PinkyCharacter, DeltaTime);
    CheckCollisionWithWalls(Pinky, PinkyCharacter);
    EnemyController(Pinky, PinkyCharacter);
}

void GameLogic::EnemyController(std::shared_ptr<GameEntity> Entity, Character &Character)
{
    if (PacmanCharacter.Position.x >= Character.Position.x)
    {
        Character.Direction = Directions::Right;
    }
    if (PacmanCharacter.Position.x <= Character.Position.x)
    {
        Character.Direction = Directions::Left;
    }
    if (PacmanCharacter.Position.y <= Character.Position.y)
    {
        Character.Direction = Directions::Up;
    }
    if (PacmanCharacter.Position.y >= Character.Position.y)
    {
        Character.Direction = Directions::Down;
    }

    switch (Character.Direction)
    {
    case Directions::Up:
        Character.Position.y -= Character.UpVelocity;
        Entity->SetPosition(Character.Position.x, Character.Position.y);
        break;
    case Directions::Down:
        Character.Position.y += Character.DownVelocity;
        Entity->SetPosition(Character.Position.x, Character.Position.y);
        break;
    case Directions::Left:
        Character.Position.x -= Character.LeftVelocity;
        Entity->SetPosition(Character.Position.x, Character.Position.y);
        break;
    case Directions::Right:
        Character.Position.x += Character.RightVelocity;
        Entity->SetPosition(Character.Position.x, Character.Position.y);
        break;
    default:
        break;
    }
}

void GameLogic::SetStartingPositions()
{
    PacmanCharacter.Position = {420.f, 620.f};
    PacmanCharacter.Speed = 2;
    BlinkyCharacter.Position = {220.f, 220.f};
    ClydeCharacter.Position = {400.f, 400.f};
    InkyCharacter.Position = {500.f, 500.f};
    PinkyCharacter.Position = {620.f, 620.f};
}

void GameLogic::InitializeCharacter(std::shared_ptr<GameEntity> &Entity, std::vector<std::shared_ptr<GameEntity>> &EntityVector, const float PosX, const float PosY, const char *FilePath, const float Rotation, const float Scale)
{
    Entity->AddPositionComponent();
    Entity->AddVelocityComponent();
    Entity->AddSprite2DComponent(FilePath);
    Entity->SetPosition(PosX, PosY);
    Entity->SetRotation(Rotation);
    Entity->SetScale(Scale);
    EntityVector.emplace_back(Entity);
    GameEntities.emplace_back(Entity);
}
