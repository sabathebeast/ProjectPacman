#include "GameLogic.h"
#include <GameEntity.h>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>

int MazeMap[CELL_ROWS][CELL_COLS] =
    {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1,
        1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1,
        1, 2, 1, 3, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 3, 1, 2, 1,
        1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 4, 1, 1, 0, 1, 2, 1, 1, 1, 1, 1, 1, 1,
        7, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 0, 0, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 6,
        1, 1, 1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 2, 1, 0, 0, 0, 0, 0, 0, 0, 1, 2, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 1, 1, 0, 1, 2, 1, 1, 1, 1, 1, 1, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1,
        1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 5, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1,
        1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1,
        1, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1,
        1, 2, 2, 3, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 3, 2, 2, 1,
        1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 2, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

int SzandraMap[CELL_ROWS][CELL_COLS] =
    {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 2, 2, 2, 2, 1, 1, 1, 2, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 2, 1,
        0, 0, 2, 2, 5, 2, 2, 2, 2, 1, 1, 1, 2, 1, 1, 2, 2, 2, 1, 1, 2, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 1, 1, 2, 2, 2, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 2, 0, 0, 0, 0, 0,
        1, 1, 1, 2, 1, 1, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1,
        1, 2, 1, 0, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 2, 2, 2, 2, 2, 1,
        1, 2, 0, 0, 0, 1, 1, 1, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 1, 1, 1, 1, 1,
        1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 2, 2, 3, 2, 2, 1,
        1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

Character PacmanCharacter;
Character BlinkyCharacter;
Character ClydeCharacter;
Character InkyCharacter;
Character PinkyCharacter;

Timer PacmanStateTimer;
Timer PacmanTimer;
Timer PowerUpTimer;
Timer StartGameDelayTimer;
Timer ClydeTimer;
Timer PinkyTimer;
Timer InkyTimer;
Timer ScatterTimer;
Timer ChaseTimer;

std::shared_ptr<GameEntity> Pacman = std::make_shared<GameEntity>("Pacman");
std::shared_ptr<GameEntity> Blinky = std::make_shared<GameEntity>("Blinky");
std::shared_ptr<GameEntity> Clyde = std::make_shared<GameEntity>("Clyde");
std::shared_ptr<GameEntity> Inky = std::make_shared<GameEntity>("Inky");
std::shared_ptr<GameEntity> Pinky = std::make_shared<GameEntity>("Pinky");

GameLogic::GameLogic()
{
    AddWallsFoodAndPowerUps();
    SetStartingPositions();
    DefineEnemyAndCellType();

    InitCharacter(Pacman, EnemyEntities, PacmanCharacter.Position.x, PacmanCharacter.Position.y, "./Assets/Pacman32.png", 270.f, 0.25f, 0.75f, 3);
    InitCharacter(Blinky, EnemyEntities, BlinkyCharacter.Position.x, BlinkyCharacter.Position.y, "./Assets/GhostBody32.png", 0.f, 0.125f, 0.75f, 6, 0.f, BlinkyColor);
    InitCharacter(Clyde, EnemyEntities, ClydeCharacter.Position.x, ClydeCharacter.Position.y, "./Assets/GhostBody32.png", 0.f, 0.125f, 0.75f, 6, 0.f, ClydeColor);
    InitCharacter(Inky, EnemyEntities, InkyCharacter.Position.x, InkyCharacter.Position.y, "./Assets/GhostBody32.png", 0.f, 0.125f, 0.75f, 6, 0.f, InkyColor);
    InitCharacter(Pinky, EnemyEntities, PinkyCharacter.Position.x, PinkyCharacter.Position.y, "./Assets/GhostBody32.png", 0.f, 0.125f, 0.75f, 6, 0.f, PinkyColor);

    InitAudioDevice();
    CreditSound = LoadSound("./Sounds/credit.wav");
    StartSound = LoadSound("./Sounds/game_start.wav");
    PacmanDeadSound = LoadSound("./Sounds/death_1.wav");
    PacmanDeadSoundEndPutty = LoadSound("./Sounds/death_2.wav");
    PowerUpSound = LoadSound("./Sounds/power_pellet.wav");
    EnemyDeadSound = LoadSound("./Sounds/eat_ghost.wav");
    RetreatingSound = LoadSound("./Sounds/retreating.wav");
    ChaseModeSound = LoadSound("./Sounds/ChaseMode.mp3");

    PacmanCharacter.Speed = 120.0;
    NumberOfPellets = PelletCount;
    PacmanDeadTexture = LoadTexture("./Assets/GameOver32.png");
    GhostEyeTexture = LoadTexture("./Assets/GhostEyes32.png");
    PacmanLifeTexture = LoadTexture("./Assets/Pacman.png");
    StartTimer(StartGameDelayTimer);

    PacmanCharacter.Direction = Directions::Right;
}

GameLogic::~GameLogic()
{
    UnloadSound(CreditSound);
    UnloadSound(StartSound);
    UnloadSound(PacmanDeadSound);
    UnloadSound(PowerUpSound);
    UnloadSound(EnemyDeadSound);
    UnloadSound(PacmanDeadSoundEndPutty);
    UnloadSound(RetreatingSound);
    CloseAudioDevice();
    UnloadTexture(WallTexture);
    UnloadTexture(FoodTexture);
    UnloadTexture(GateTexture);
    UnloadTexture(PacmanLifeTexture);
}

void GameLogic::Render()
{
    for (int i = 0; i < (int)GameEntities.size(); i++)
    {
        if (GameEntities[i]->CellType == CellType::Food || GameEntities[i]->CellType == CellType::PowerUp)
        {
            Rectangle PacmanRec = {Pacman->GetPosition().x - Pacman->GetTexture().width * Pacman->GetWidthScale() / 2, Pacman->GetPosition().y - Pacman->GetTexture().height * Pacman->GetHeightScale() / 2, Pacman->GetTexture().width * Pacman->GetWidthScale(), Pacman->GetTexture().height * Pacman->GetHeightScale()};
            Rectangle FoodRec = {GameEntities[i]->GetPosition().x - GameEntities[i]->GetTexture().width * GameEntities[i]->GetWidthScale() / 2, GameEntities[i]->GetPosition().y - GameEntities[i]->GetTexture().height * GameEntities[i]->GetHeightScale() / 2, GameEntities[i]->GetTexture().width * GameEntities[i]->GetWidthScale(), GameEntities[i]->GetTexture().height * GameEntities[i]->GetHeightScale()};

            if (CheckCollisionRecs(PacmanRec, FoodRec))
            {
                if (GameEntities[i]->CellType == CellType::PowerUp)
                {
                    Score += 50;
                    PelletCount--;
                    PlaySound(PowerUpSound);
                    Pacman->State = State::PowerUp;
                    StartTimer(PacmanStateTimer);
                    for (int j = 0; j < (int)GameEntities.size(); j++)
                    {
                        if (GameEntities[j]->CellType == CellType::Enemy)
                        {
                            if (GameEntities[j]->EnemyType == Enemy::Blinky)
                            {
                                continue;
                            }
                            GameEntities[j]->SetTextureColor(BLUE);
                        }
                    }
                }
                else
                {
                    Score += 10;
                    PelletCount--;
                    PlaySound(CreditSound);
                }
                GameEntities.erase(GameEntities.begin() + i);
            }
        }

        if (GameEntities[i]->CellType == CellType::PowerUp)
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

void GameLogic::Update()
{
    const float DeltaTime = GetFrameTime();
    AddStartGameDelay(5.0);
    UpdateEntities(DeltaTime);
    PlayPacmanDeadAnimation();
    GameMode(10.0, 30.0, 10, 30.0, 5.0, 30.0);
    AddLife();
    ResetCharactersStatesAndGameOver();
    CheckPelletCount();
    SetPowerUpBehaviour(0.5, 0.3);
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
        SetStartingPositions();
        NextDirection = Directions::None;
        PacmanCharacter.Direction = Directions::None;
        Pacman->SetPosition(PacmanCharacter.Position.x, PacmanCharacter.Position.y);
        Pacman->SetRotation(270.f);
        StartDelay = false;
        Pacman->isCurrentlyDead = false;
        PacmanLives--;
    }
}

void GameLogic::ResetEnemyAndDrawScore(double time, const Timer &EnemyTimer, Character &EnemyCharacter, std::shared_ptr<GameEntity> &EnemyEntity)
{
    double currentTime = GetTime();
    if (currentTime >= EnemyTimer.LifeTime + time)
    {
        EnemyCharacter.isEaten = false;
        EnemyEntity->IsDead = false;
        switch (EnemyEntity->EnemyType)
        {
        case Enemy::Clyde:
            EnemyEntity->SetTextureColor(ClydeColor);
            ClydeCharacter.ScoreMultiplyer = 0;
            ClydeCharacter.Speed = 96.0;
            break;
        case Enemy::Pinky:
            EnemyEntity->SetTextureColor(PinkyColor);
            PinkyCharacter.ScoreMultiplyer = 0;
            PinkyCharacter.Speed = 96.0;
            break;
        case Enemy::Inky:
            EnemyEntity->SetTextureColor(InkyColor);
            InkyCharacter.ScoreMultiplyer = 0;
            InkyCharacter.Speed = 96.0;
            break;
        default:
            break;
        }
    }
    if (currentTime < EnemyTimer.LifeTime + (time - 1.0))
    {
        DrawText(TextFormat("%i", (EnemyCharacter.ScoreMultiplyer * GhostScore)), (int)EnemyCharacter.DeathPosition.x - CELL_SIZE / 2, (int)EnemyCharacter.DeathPosition.y - CELL_SIZE / 2, CELL_SIZE, ORANGE);
    }
}

void GameLogic::PlayEnemyAnimation(Character &Source, std::shared_ptr<GameEntity> &EntityToMove)
{
    Source.FrameCount++;
    if (Source.FrameCount >= (GetFPS() / Source.FrameSpeed))
    {
        Source.FrameCount = 0;
        Source.CurrentFrame++;
        if (Source.CurrentFrame > 6)
        {
            Source.CurrentFrame = 0;
        }
        EntityToMove->SetTextureSourceX(Source.CurrentFrame * EntityToMove->GetTexture().width / EntityToMove->GetTextureFrames());
    }
    if (Source.Direction == Directions::Up)
    {
        DrawTextureRec(GhostEyeTexture, Rectangle{1 * (float)GhostEyeTexture.width / 5 + 3, 0.f, (float)GhostEyeTexture.width * 0.75f / 5, (float)GhostEyeTexture.height * 0.75f}, {Source.Position.x - CELL_SIZE / 2, Source.Position.y - CELL_SIZE / 2}, WHITE);
    }
    if (Source.Direction == Directions::Down)
    {
        DrawTextureRec(GhostEyeTexture, Rectangle{3 * (float)GhostEyeTexture.width / 5 + 3, 0.f, (float)GhostEyeTexture.width * 0.75f / 5, (float)GhostEyeTexture.height * 0.75f}, {Source.Position.x - CELL_SIZE / 2, Source.Position.y - CELL_SIZE / 2}, WHITE);
    }
    if (Source.Direction == Directions::Left)
    {
        DrawTextureRec(GhostEyeTexture, Rectangle{2 * (float)GhostEyeTexture.width / 5, 0.f, (float)GhostEyeTexture.width * 0.75f / 5, (float)GhostEyeTexture.height * 0.75f}, {Source.Position.x - CELL_SIZE / 2, Source.Position.y - CELL_SIZE / 2}, WHITE);
    }
    if (Source.Direction == Directions::Right)
    {
        DrawTextureRec(GhostEyeTexture, Rectangle{0 * (float)GhostEyeTexture.width / 5 + 3, 0.f, (float)GhostEyeTexture.width * 0.75f / 5, (float)GhostEyeTexture.height * 0.75f}, {Source.Position.x - CELL_SIZE / 2 - 3, Source.Position.y - CELL_SIZE / 2}, WHITE);
    }
    if (Source.Direction == Directions::None)
    {
        DrawTextureRec(GhostEyeTexture, Rectangle{3 * (float)GhostEyeTexture.width / 5 + 3, 0.f, (float)GhostEyeTexture.width * 0.75f / 5, (float)GhostEyeTexture.height * 0.75f}, {Source.Position.x - CELL_SIZE / 2 - 3, Source.Position.y - CELL_SIZE / 2}, WHITE);
    }
}

void GameLogic::ChangeToChaseMode(double time)
{
    double currentTime = GetTime();
    if (currentTime >= ScatterTimer.LifeTime + time)
    {
        isChase = true;
        SetStateChase();
    }
}

void GameLogic::ChangeToScatterMode(double time)
{
    double currentTime = GetTime();
    if (currentTime >= ChaseTimer.LifeTime + time)
    {
        isChase = false;
        isScatter = true;
        StopSound(ChaseModeSound);
        ChaseScatterRoundCount++;
    }
}

void GameLogic::GameOver()
{
    Pacman->IsDead = true;
    int GameOverTexTSize = MeasureText("GAME OVER!", 80);
    DrawText("GAME OVER!", GetScreenWidth() / 2 - GameOverTexTSize / 2, GetScreenHeight() / 2 - 50, 80, RED);
}

void GameLogic::CheckPelletCount()
{
    if (PelletCount == 0)
    {
        int GameOverTexTSize = MeasureText("YOU WON!", 100);
        DrawText("YOU WON!", GetScreenWidth() / 2 - GameOverTexTSize / 2, GetScreenHeight() / 2 - 50, 100, RED);
    }
}

void GameLogic::SetPowerUpBehaviour(double Frequency, double ResetTime)
{
    if (eventTriggered(Frequency))
    {
        StartTimer(PowerUpTimer);
        IsPowerUpEnabled = false;
    }

    if (!IsPowerUpEnabled)
    {
        ResetPowerUp(ResetTime);
    }
}

void GameLogic::AddStartGameDelay(double StartDelayAmount)
{
    if (IsStartGameDelay)
    {
        ResetStartGameDelayTimer(StartDelayAmount);
    }
}

void GameLogic::GameMode(double FirstScatteringTime, double FirstChasingTime, double SecondScatteringTime, double SecondChasingTime, double ThirdScatteringTime, double ThirdChasingTime)
{
    if (ChaseScatterRoundCount == 0 && !IsStartGameDelay)
    {
        if (isScatter)
        {
            SetStateScatter();
        }
        else
        {
            if (!isChase)
            {
                ChangeToChaseMode(FirstScatteringTime);
            }
        }

        if (isChase)
        {
            if (!IsSoundPlaying(ChaseModeSound))
            {
                PlaySound(ChaseModeSound);
            }
            ChangeToScatterMode(FirstChasingTime);
        }
    }
    if (ChaseScatterRoundCount == 1)
    {
        if (isScatter)
        {
            SetStateScatter();
        }
        else
        {
            if (!isChase)
            {
                ChangeToChaseMode(SecondScatteringTime);
            }
        }

        if (isChase)
        {
            if (!IsSoundPlaying(ChaseModeSound))
            {
                PlaySound(ChaseModeSound);
            }
            ChangeToScatterMode(SecondChasingTime);
        }
    }
    if (ChaseScatterRoundCount == 2)
    {
        if (isScatter)
        {
            SetStateScatter();
        }
        else
        {
            if (!isChase)
            {
                ChangeToChaseMode(ThirdScatteringTime);
            }
        }

        if (isChase)
        {
            if (!IsSoundPlaying(ChaseModeSound))
            {
                PlaySound(ChaseModeSound);
            }
            ChangeToScatterMode(ThirdChasingTime);
        }
    }
    if (ChaseScatterRoundCount == 3)
    {
        if (isScatter)
        {
            SetStateScatter();
        }
        else
        {
            if (!isChase)
            {
                ChangeToChaseMode(ThirdScatteringTime);
            }
        }

        if (isChase)
        {
            if (!IsSoundPlaying(ChaseModeSound))
            {
                PlaySound(ChaseModeSound);
            }
        }
    }
}

void GameLogic::SetStateScatter()
{
    for (auto enemy : EnemyEntities)
    {
        if (enemy->CellType != CellType::Pacman)
        {
            enemy->State = State::Scatter;
        }
    }
    StartTimer(ScatterTimer);
    isScatter = false;
}

void GameLogic::SetStateChase()
{
    for (auto enemy : EnemyEntities)
    {
        if (enemy->CellType != CellType::Pacman)
        {
            enemy->State = State::Chase;
        }
    }
    StartTimer(ChaseTimer);
}

void GameLogic::ResetCharactersStatesAndGameOver()
{
    if (Pacman->State == State::PowerUp)
    {
        ResetPacmanState(PowerUpTime);
    }
    if (ClydeCharacter.isEaten)
    {
        ResetEnemyAndDrawScore(7.0, ClydeTimer, ClydeCharacter, Clyde);
    }
    if (PinkyCharacter.isEaten)
    {
        ResetEnemyAndDrawScore(7.0, PinkyTimer, PinkyCharacter, Pinky);
    }
    if (InkyCharacter.isEaten)
    {
        ResetEnemyAndDrawScore(7.0, InkyTimer, InkyCharacter, Inky);
    }
    if (StartDelay)
    {
        if (PacmanLives > 0)
        {
            ResetPacman(3.0);
        }
        else
        {
            GameOver();
        }
    }
}

void GameLogic::AddLife()
{
    if (!IsLifeAdded)
    {
        if (Score >= 5000)
        {
            PacmanLives++;
            IsLifeAdded = true;
        }
    }
}

void GameLogic::ResetPacmanState(double time)
{
    double currentTime = GetTime();
    if (currentTime <= PacmanStateTimer.LifeTime + time)
    {
        Pacman->SetTextureColor(RED);
        Pacman->State = State::PowerUp;
        PacmanCharacter.Speed = 180.0;
        isPowerUpState = true;
        if (!IsSoundPlaying(RetreatingSound))
        {
            PlaySound(RetreatingSound);
        }
    }
    else
    {
        Pacman->SetTextureColor(YELLOW);
        Pacman->State = State::Nothing;
        PacmanCharacter.Speed = 120.0;
        isPowerUpState = false;
        EatenGhostCount = 0;
        for (int j = 0; j < (int)GameEntities.size(); j++)
        {
            if (GameEntities[j]->CellType == CellType::Enemy)
            {
                if (!GameEntities[j]->IsDead)
                {
                    switch (GameEntities[j]->EnemyType)
                    {
                    case Enemy::Clyde:
                        GameEntities[j]->SetTextureColor(ClydeColor);
                        break;
                    case Enemy::Pinky:
                        GameEntities[j]->SetTextureColor(PinkyColor);
                        break;
                    case Enemy::Inky:
                        GameEntities[j]->SetTextureColor(InkyColor);
                        break;
                    default:
                        break;
                    }
                }
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
    DrawText("FOR", 25, 225, 60, RED);
    DrawText("EVER", GetScreenWidth() - 168, 320, 60, RED);
    DrawText("PAC", 25, 320, 60, YELLOW);
    DrawText("MAN", GetScreenWidth() - 145, 225, 60, YELLOW);
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
    DrawText(ScoreText, 10, GetScreenHeight() - 20, 20, WHITE);
    DrawText(TextFormat("%i", Score), 20 + ScoreTextSize, GetScreenHeight() - 20, 20, WHITE);
}

void GameLogic::UpdateEntities(const float &DeltaTime)
{
    if (!StartDelay && !IsStartGameDelay && PelletCount > 0)
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
}

void GameLogic::PacmanCollisionWithEnemy(std::vector<std::shared_ptr<GameEntity>> &EnemyEntityVector)
{
    for (auto enemy : EnemyEntities)
    {
        if (enemy->CellType == CellType::Pacman)
            continue;
        Rectangle PacmanRec = {Pacman->GetPosition().x - Pacman->GetTexture().width * Pacman->GetWidthScale() / 2, Pacman->GetPosition().y - Pacman->GetTexture().height * Pacman->GetHeightScale() / 2, Pacman->GetTexture().width * Pacman->GetWidthScale(), Pacman->GetTexture().height * Pacman->GetHeightScale()};
        Rectangle EnemyRec = {enemy->GetPosition().x - enemy->GetTexture().width * enemy->GetWidthScale() / 2, enemy->GetPosition().y - enemy->GetTexture().height * enemy->GetHeightScale() / 2, enemy->GetTexture().width * enemy->GetWidthScale(), enemy->GetTexture().height * enemy->GetHeightScale()};
        if (CheckCollisionRecs(PacmanRec, EnemyRec))
        {
            if ((Pacman->State == State::Nothing && !enemy->IsDead) || (Pacman->State == State::PowerUp && enemy->EnemyType == Enemy::Blinky))
            {
                Pacman->isCurrentlyDead = true;
                StartTimer(PacmanTimer);
                StartDelay = true;
                PlaySound(PacmanDeadSound);
                ChaseScatterRoundCount = 0;
                isScatter = true;
                isChase = false;
                StopSound(ChaseModeSound);
            }
            if (Pacman->State == State::PowerUp)
            {
                if (enemy->EnemyType == Enemy::Blinky)
                {
                    continue;
                }
                if (!enemy->IsDead)
                {
                    EatenGhostCount++;
                    for (int i = 0; i < EatenGhostCount; i++)
                    {
                        Score += 400;
                    }

                    switch (enemy->EnemyType)
                    {
                    case Enemy::Clyde:
                        ClydeCharacter.isEaten = true;
                        ClydeCharacter.DeathPosition = {ClydeCharacter.Position.x, ClydeCharacter.Position.y};
                        ClydeCharacter.ScoreMultiplyer = EatenGhostCount;
                        ClydeCharacter.Speed = 240.0;
                        StartTimer(ClydeTimer);
                        break;
                    case Enemy::Inky:
                        InkyCharacter.isEaten = true;
                        InkyCharacter.DeathPosition = {InkyCharacter.Position.x, InkyCharacter.Position.y};
                        InkyCharacter.ScoreMultiplyer = EatenGhostCount;
                        InkyCharacter.Speed = 240.0;
                        StartTimer(InkyTimer);
                        break;
                    case Enemy::Pinky:
                        PinkyCharacter.isEaten = true;
                        PinkyCharacter.DeathPosition = {PinkyCharacter.Position.x, PinkyCharacter.Position.y};
                        PinkyCharacter.ScoreMultiplyer = EatenGhostCount;
                        PinkyCharacter.Speed = 240.0;
                        StartTimer(PinkyTimer);
                        break;
                    default:
                        break;
                    }

                    enemy->IsDead = true;
                    PlaySound(EnemyDeadSound);
                }
            }
        }
    }
}

void GameLogic::PacmanMove(const float &DeltaTime)
{
    int PacmanHalfSize = CELL_SIZE / 2;
    int NewPacmanX = PacmanCharacter.Position.x;
    int NewPacmanY = PacmanCharacter.Position.y;

    switch ((GetKeyPressed()))
    {
    case KEY_W:
        NextDirection = Directions::Up;
        break;
    case KEY_UP:
        NextDirection = Directions::Up;
        break;
    case KEY_S:
        NextDirection = Directions::Down;
        break;
    case KEY_DOWN:
        NextDirection = Directions::Down;
        break;
    case KEY_A:
        NextDirection = Directions::Left;
        break;
    case KEY_LEFT:
        NextDirection = Directions::Left;
        break;
    case KEY_D:
        NextDirection = Directions::Right;
        break;
    case KEY_RIGHT:
        NextDirection = Directions::Right;
        break;
    default:
        break;
    }

    if (onMobile)
    {
        if (GetTouchX() > PacmanCharacter.Position.x)
        {
            NextDirection = Directions::Right;
        }
        else
        {
            NextDirection = Directions::Left;
        }
        if (GetTouchY() > PacmanCharacter.Position.y)
        {
            NextDirection = Directions::Down;
        }
        else
        {
            NextDirection = Directions::Up;
        }
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

    int UP_Y = (NewPacmanY - PacmanHalfSize - PacmanCharacter.Speed * DeltaTime) / CELL_SIZE;
    int UP_X = (NewPacmanX - PacmanHalfSize) / CELL_SIZE;

    int DOWN_Y = (NewPacmanY + PacmanHalfSize + PacmanCharacter.Speed * DeltaTime) / CELL_SIZE;
    int DOWN_X = (NewPacmanX - PacmanHalfSize) / CELL_SIZE;

    int LEFT_Y = (NewPacmanY - PacmanHalfSize) / CELL_SIZE;
    int LEFT_X = (NewPacmanX - PacmanHalfSize - PacmanCharacter.Speed * DeltaTime) / CELL_SIZE;

    int RIGHT_Y = (NewPacmanY - PacmanHalfSize) / CELL_SIZE;
    int RIGHT_X = (NewPacmanX + PacmanHalfSize + PacmanCharacter.Speed * DeltaTime) / CELL_SIZE;

    switch (NextDirection)
    {
    case Directions::Up:
        if (CanAcceptVerticalInput && MazeMap[UP_Y][UP_X] != 1 && MazeMap[UP_Y][UP_X] != 4)
        {
            PacmanCharacter.Direction = NextDirection;
        }
        break;
    case Directions::Down:
        if (CanAcceptVerticalInput && MazeMap[DOWN_Y][DOWN_X] != 1 && MazeMap[DOWN_Y][DOWN_X] != 4)
        {
            PacmanCharacter.Direction = NextDirection;
        }
        break;
    case Directions::Left:
        if (CanAcceptHorizontalInput && MazeMap[LEFT_Y][LEFT_X] != 1 && MazeMap[LEFT_Y][LEFT_X] != 4)
        {
            PacmanCharacter.Direction = NextDirection;
        }
        break;
    case Directions::Right:
        if (CanAcceptHorizontalInput && MazeMap[RIGHT_Y][RIGHT_X] != 1 && MazeMap[RIGHT_Y][RIGHT_X] != 4)
        {
            PacmanCharacter.Direction = NextDirection;
        }
        break;
    default:
        break;
    }

    if (PacmanCharacter.Direction == Directions::Up)
    {
        FrameCount++;
        if (MazeMap[UP_Y][UP_X] != 1 && MazeMap[UP_Y][UP_X] != 4)
        {
            Pacman->SetRotation(270.f);
            PacmanCharacter.Position.y -= PacmanCharacter.Speed * DeltaTime;
            PlayPacmanAnimation();
        }
        else
        {
            PacmanCharacter.Position.y = (UP_Y + 1) * CELL_SIZE + CELL_SIZE / 2;
            Pacman->SetTextureSourceX(2 * Pacman->GetTexture().width / Pacman->GetTextureFrames());
        }
    }

    if (PacmanCharacter.Direction == Directions::Down)
    {
        FrameCount++;
        if (MazeMap[DOWN_Y][DOWN_X] != 1 && MazeMap[DOWN_Y][DOWN_X] != 4)
        {
            Pacman->SetRotation(90.f);
            PacmanCharacter.Position.y += PacmanCharacter.Speed * DeltaTime;
            PlayPacmanAnimation();
        }
        else
        {
            PacmanCharacter.Position.y = (DOWN_Y - 1) * CELL_SIZE + CELL_SIZE / 2;
            Pacman->SetTextureSourceX(2 * Pacman->GetTexture().width / Pacman->GetTextureFrames());
        }
    }

    if (PacmanCharacter.Direction == Directions::Left)
    {
        FrameCount++;
        if (MazeMap[LEFT_Y][LEFT_X] != 1 && MazeMap[LEFT_Y][LEFT_X] != 4)
        {
            Pacman->SetRotation(180.f);
            PacmanCharacter.Position.x -= PacmanCharacter.Speed * DeltaTime;
            PlayPacmanAnimation();
        }
        else
        {
            PacmanCharacter.Position.x = (LEFT_X + 1) * CELL_SIZE + CELL_SIZE / 2;
            Pacman->SetTextureSourceX(2 * Pacman->GetTexture().width / Pacman->GetTextureFrames());
        }
    }

    if (PacmanCharacter.Direction == Directions::Right)
    {
        FrameCount++;
        if (MazeMap[RIGHT_Y][RIGHT_X] != 1 && MazeMap[RIGHT_Y][RIGHT_X] != 4)
        {
            Pacman->SetRotation(0.f);
            PacmanCharacter.Position.x += PacmanCharacter.Speed * DeltaTime;
            PlayPacmanAnimation();
        }
        else
        {
            PacmanCharacter.Position.x = (RIGHT_X - 1) * CELL_SIZE + CELL_SIZE / 2;
            Pacman->SetTextureSourceX(2 * Pacman->GetTexture().width / Pacman->GetTextureFrames());
        }
    }

    Pacman->SetPosition(PacmanCharacter.Position.x, PacmanCharacter.Position.y);
    // DrawText(TextFormat("Y:%i", NewPacmanY), GetScreenWidth() - 60, GetScreenHeight() - 20, 20, WHITE);
    // DrawText(TextFormat("X:%i", NewPacmanX), GetScreenWidth() - 120, GetScreenHeight() - 20, 20, WHITE);

    PacmanCollisionWithEnemy(EnemyEntities);
    SecretDoor();
}

void GameLogic::SecretDoor()
{
    if (MazeMap[((int)PacmanCharacter.Position.y - CELL_SIZE / 2) / CELL_SIZE][((int)PacmanCharacter.Position.x - CELL_SIZE / 2) / CELL_SIZE] == 6)
    {
        PacmanCharacter.Position.x = CELL_SIZE / 2;
        Pacman->SetPosition(PacmanCharacter.Position.x, PacmanCharacter.Position.y);
    }
    if (MazeMap[((int)PacmanCharacter.Position.y - CELL_SIZE / 2) / CELL_SIZE][((int)PacmanCharacter.Position.x + CELL_SIZE / 2) / CELL_SIZE] == 7)
    {
        PacmanCharacter.Position.x = 24 * CELL_SIZE + CELL_SIZE / 2;
        Pacman->SetPosition(PacmanCharacter.Position.x, PacmanCharacter.Position.y);
    }
}

void GameLogic::PlayPacmanAnimation()
{
    if (FrameCount >= (GetFPS() / FrameSpeed))
    {
        FrameCount = 0;
        CurrentFrame++;
        if (CurrentFrame > 2)
        {
            CurrentFrame = 0;
        }
        Pacman->SetTextureSourceX(CurrentFrame * Pacman->GetTexture().width / Pacman->GetTextureFrames());
    }
}

void GameLogic::PlayPacmanDeadAnimation()
{
    if (Pacman->isCurrentlyDead && !Pacman->IsDead)
    {
        PacmanDeadFrameCount++;

        if (PacmanDeadFrameCount >= (GetFPS() / PacmanDeadFrameSpeed))
        {
            PacmanDeadFrameCount = 0;
            PacmanDeadCurrentFrame++;
            if (PacmanDeadCurrentFrame == 9)
            {
                PlaySound(PacmanDeadSoundEndPutty);
            }
            if (PacmanDeadCurrentFrame == 10)
            {
                PacmanDeadCurrentFrame = 0;
                PacmanDeadFrameCount = 60;
            }
            PacmanDeadSourceX = (float)PacmanDeadCurrentFrame * ((float)PacmanDeadTexture.width / (float)PacmanDeadFrames);
        }
        DrawTexturePro(PacmanDeadTexture, Rectangle{PacmanDeadSourceX, 0.f, (float)PacmanDeadTexture.width / PacmanDeadFrames, (float)PacmanDeadTexture.height}, Rectangle{PacmanCharacter.Position.x, PacmanCharacter.Position.y, PacmanDeadTexture.width * 0.75f / PacmanDeadFrames, PacmanDeadTexture.height * 0.75f}, {PacmanDeadTexture.width / PacmanDeadFrames * 0.75f / 2, PacmanDeadTexture.height * 0.75f / 2}, Pacman->GetRotation(), WHITE);
    }
}

void GameLogic::DrawPacmanLives()
{
    for (int i = 0; i < PacmanLives; i++)
    {
        int Offset{30};
        DrawTextureEx(PacmanLifeTexture, {GetScreenWidth() / 2.0f - 40 + i * Offset, GetScreenHeight() - 22.0f}, 0.f, 0.035f, WHITE);
    }
}

void GameLogic::EnemyMove(const float &DeltaTime, Character &Source, const Character &Destination, std::vector<int> &PathfindingTrailX, std::vector<int> &PathfindingTrailY, std::shared_ptr<GameEntity> &EntityToMove)
{
    Pair src = std::make_pair(((int)Source.Position.y - CELL_SIZE / 2) / CELL_SIZE, ((int)Source.Position.x - CELL_SIZE / 2) / CELL_SIZE);
    Pair dest = std::make_pair(((int)Destination.Position.y - CELL_SIZE / 2) / CELL_SIZE, ((int)Destination.Position.x - CELL_SIZE / 2) / CELL_SIZE);

    if (!isValid(dest.first, dest.second) || !isValid(src.first, src.second) || !isUnBlocked(MazeMap, dest.first, dest.second) || !isUnBlocked(MazeMap, src.first, src.second))
    {
        src = std::make_pair(((int)Source.Position.y - CELL_SIZE / 2) / CELL_SIZE, ((int)Source.Position.x - CELL_SIZE / 2) / CELL_SIZE);
        dest = std::make_pair(((int)Destination.Position.y - CELL_SIZE / 2) / CELL_SIZE, ((int)Destination.Position.x - CELL_SIZE / 2) / CELL_SIZE);
    }

    if (isDestination(src.first, src.second, dest) == true)
    {
        Source.Direction = Directions::None;
    }
    else
    {
        AStarSearch(MazeMap, src, dest, PathfindingTrailX, PathfindingTrailY);

        int HalfSize = CELL_SIZE / 2;
        int NewX = Source.Position.x;
        int NewY = Source.Position.y;

        int UP_Y = (NewY - HalfSize - Source.Speed * DeltaTime) / CELL_SIZE;
        int UP_X = (NewX - HalfSize) / CELL_SIZE;

        int DOWN_Y = (NewY + HalfSize + Source.Speed * DeltaTime) / CELL_SIZE;
        int DOWN_X = (NewX - HalfSize) / CELL_SIZE;

        int LEFT_Y = (NewY - HalfSize) / CELL_SIZE;
        int LEFT_X = (NewX - HalfSize - Source.Speed * DeltaTime) / CELL_SIZE;

        int RIGHT_Y = (NewY - HalfSize) / CELL_SIZE;
        int RIGHT_X = (NewX + HalfSize + Source.Speed * DeltaTime) / CELL_SIZE;

        if (PathfindingTrailY[1] > (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE && PathfindingTrailX[1] == (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE)
        {
            Source.Direction = Directions::Right;
        }
        if (PathfindingTrailY[1] < (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE && PathfindingTrailX[1] == (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE)
        {
            Source.Direction = Directions::Left;
        }
        if (PathfindingTrailX[1] > (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE && PathfindingTrailY[1] == (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE)
        {
            Source.Direction = Directions::Down;
        }
        if (PathfindingTrailX[1] < (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE && PathfindingTrailY[1] == (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE)
        {
            Source.Direction = Directions::Up;
        }

        if (Source.Direction == Directions::Up)
        {
            if (MazeMap[UP_Y][UP_X] != 1 && PathfindingTrailX[1] <= (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE)
            {
                Source.Position.y -= Source.Speed * DeltaTime;
                PlayEnemyAnimation(Source, EntityToMove);
            }
            else
            {
                Source.Position.y = (UP_Y + 1) * CELL_SIZE + CELL_SIZE / 2;
                EntityToMove->SetTextureSourceX(2 * EntityToMove->GetTexture().width / EntityToMove->GetTextureFrames());
            }
        }
        if (Source.Direction == Directions::Down)
        {
            if (MazeMap[DOWN_Y][DOWN_X] != 1 && PathfindingTrailX[1] >= (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE)
            {
                Source.Position.y += Source.Speed * DeltaTime;
                PlayEnemyAnimation(Source, EntityToMove);
            }
            else
            {
                Source.Position.y = (DOWN_Y - 1) * CELL_SIZE + CELL_SIZE / 2;
                EntityToMove->SetTextureSourceX(2 * EntityToMove->GetTexture().width / EntityToMove->GetTextureFrames());
            }
        }
        if (Source.Direction == Directions::Left)
        {
            if (MazeMap[LEFT_Y][LEFT_X] != 1 && MazeMap[LEFT_Y][LEFT_X] != 4 && PathfindingTrailY[1] <= (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE)
            {
                Source.Position.x -= Source.Speed * DeltaTime;
                PlayEnemyAnimation(Source, EntityToMove);
            }
            else
            {
                Source.Position.x = (LEFT_X + 1) * CELL_SIZE + CELL_SIZE / 2;
                EntityToMove->SetTextureSourceX(2 * EntityToMove->GetTexture().width / EntityToMove->GetTextureFrames());
            }
        }
        if (Source.Direction == Directions::Right)
        {
            if (MazeMap[RIGHT_Y][RIGHT_X] != 1 && MazeMap[RIGHT_Y][RIGHT_X] != 4 && PathfindingTrailY[1] >= (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE)
            {
                Source.Position.x += Source.Speed * DeltaTime;
                PlayEnemyAnimation(Source, EntityToMove);
            }
            else
            {
                Source.Position.x = (RIGHT_X - 1) * CELL_SIZE + CELL_SIZE / 2;
                EntityToMove->SetTextureSourceX(2 * EntityToMove->GetTexture().width / EntityToMove->GetTextureFrames());
            }
        }

        EntityToMove->SetPosition(Source.Position.x, Source.Position.y);
    }

    PathfindingTrailX.clear();
    PathfindingTrailY.clear();
}

void GameLogic::EnemyMove2StepsAheadPacman(const float &DeltaTime, Character &Source, const Character &Destination, std::vector<int> &PathfindingTrailX, std::vector<int> &PathfindingTrailY, std::shared_ptr<GameEntity> &EntityToMove)
{
    Pair src = std::make_pair(((int)Source.Position.y - CELL_SIZE / 2) / CELL_SIZE, ((int)Source.Position.x - CELL_SIZE / 2) / CELL_SIZE);
    Pair CurrentDest;

    if (PacmanCharacter.Direction == Directions::Up)
    {
        CurrentDest = std::make_pair((((int)Destination.Position.y - CELL_SIZE / 2) / CELL_SIZE) - 2, ((int)Destination.Position.x - CELL_SIZE / 2) / CELL_SIZE);
    }
    if (PacmanCharacter.Direction == Directions::Down)
    {
        CurrentDest = std::make_pair((((int)Destination.Position.y - CELL_SIZE / 2) / CELL_SIZE) + 2, ((int)Destination.Position.x - CELL_SIZE / 2) / CELL_SIZE);
    }
    if (PacmanCharacter.Direction == Directions::Left)
    {
        CurrentDest = std::make_pair(((int)Destination.Position.y - CELL_SIZE / 2) / CELL_SIZE, (((int)Destination.Position.x - CELL_SIZE / 2) / CELL_SIZE) - 2);
    }
    if (PacmanCharacter.Direction == Directions::Right)
    {
        CurrentDest = std::make_pair(((int)Destination.Position.y - CELL_SIZE / 2) / CELL_SIZE, (((int)Destination.Position.x - CELL_SIZE / 2) / CELL_SIZE) + 2);
    }
    if (!isValid(CurrentDest.first, CurrentDest.second) || !isValid(src.first, src.second) || !isUnBlocked(MazeMap, CurrentDest.first, CurrentDest.second) || !isUnBlocked(MazeMap, src.first, src.second))
    {
        src = std::make_pair(((int)Source.Position.y - CELL_SIZE / 2) / CELL_SIZE, ((int)Source.Position.x - CELL_SIZE / 2) / CELL_SIZE);
        CurrentDest = std::make_pair(((int)Destination.Position.y - CELL_SIZE / 2) / CELL_SIZE, ((int)Destination.Position.x - CELL_SIZE / 2) / CELL_SIZE);
    }

    Pair dest = CurrentDest;

    if (isDestination(src.first, src.second, dest) == true)
    {
        /* Source.Direction = Directions::None; */
    }
    else
    {
        AStarSearch(MazeMap, src, dest, PathfindingTrailX, PathfindingTrailY);

        int HalfSize = CELL_SIZE / 2;
        int NewX = Source.Position.x;
        int NewY = Source.Position.y;

        int UP_Y = (NewY - HalfSize - Source.Speed * DeltaTime) / CELL_SIZE;
        int UP_X = (NewX - HalfSize) / CELL_SIZE;

        int DOWN_Y = (NewY + HalfSize + Source.Speed * DeltaTime) / CELL_SIZE;
        int DOWN_X = (NewX - HalfSize) / CELL_SIZE;

        int LEFT_Y = (NewY - HalfSize) / CELL_SIZE;
        int LEFT_X = (NewX - HalfSize - Source.Speed * DeltaTime) / CELL_SIZE;

        int RIGHT_Y = (NewY - HalfSize) / CELL_SIZE;
        int RIGHT_X = (NewX + HalfSize + Source.Speed * DeltaTime) / CELL_SIZE;

        if (PathfindingTrailY[1] > (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE && PathfindingTrailX[1] == (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE)
        {
            Source.Direction = Directions::Right;
        }
        if (PathfindingTrailY[1] < (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE && PathfindingTrailX[1] == (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE)
        {
            Source.Direction = Directions::Left;
        }
        if (PathfindingTrailX[1] > (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE && PathfindingTrailY[1] == (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE)
        {
            Source.Direction = Directions::Down;
        }
        if (PathfindingTrailX[1] < (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE && PathfindingTrailY[1] == (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE)
        {
            Source.Direction = Directions::Up;
        }

        if (Source.Direction == Directions::Up)
        {
            if (MazeMap[UP_Y][UP_X] != 1 && PathfindingTrailX[1] <= (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE)
            {
                Source.Position.y -= Source.Speed * DeltaTime;
                PlayEnemyAnimation(Source, EntityToMove);
            }
            else
            {
                Source.Position.y = (UP_Y + 1) * CELL_SIZE + CELL_SIZE / 2;
                EntityToMove->SetTextureSourceX(2 * EntityToMove->GetTexture().width / EntityToMove->GetTextureFrames());
            }
        }
        if (Source.Direction == Directions::Down)
        {
            if (MazeMap[DOWN_Y][DOWN_X] != 1 && PathfindingTrailX[1] >= (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE)
            {
                Source.Position.y += Source.Speed * DeltaTime;
                PlayEnemyAnimation(Source, EntityToMove);
            }
            else
            {
                Source.Position.y = (DOWN_Y - 1) * CELL_SIZE + CELL_SIZE / 2;
                EntityToMove->SetTextureSourceX(2 * EntityToMove->GetTexture().width / EntityToMove->GetTextureFrames());
            }
        }
        if (Source.Direction == Directions::Left)
        {
            if (MazeMap[LEFT_Y][LEFT_X] != 1 && MazeMap[LEFT_Y][LEFT_X] != 4 && PathfindingTrailY[1] <= (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE)
            {
                Source.Position.x -= Source.Speed * DeltaTime;
                PlayEnemyAnimation(Source, EntityToMove);
            }
            else
            {
                Source.Position.x = (LEFT_X + 1) * CELL_SIZE + CELL_SIZE / 2;
                EntityToMove->SetTextureSourceX(2 * EntityToMove->GetTexture().width / EntityToMove->GetTextureFrames());
            }
        }
        if (Source.Direction == Directions::Right)
        {
            if (MazeMap[RIGHT_Y][RIGHT_X] != 1 && MazeMap[RIGHT_Y][RIGHT_X] != 4 && PathfindingTrailY[1] >= (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE)
            {
                Source.Position.x += Source.Speed * DeltaTime;
                PlayEnemyAnimation(Source, EntityToMove);
            }
            else
            {
                Source.Position.x = (RIGHT_X - 1) * CELL_SIZE + CELL_SIZE / 2;
                EntityToMove->SetTextureSourceX(2 * EntityToMove->GetTexture().width / EntityToMove->GetTextureFrames());
            }
        }

        EntityToMove->SetPosition(Source.Position.x, Source.Position.y);
    }

    PathfindingTrailX.clear();
    PathfindingTrailY.clear();
}

void GameLogic::FallBackToBase(const float &DeltaTime, Character &Source, int PositionX, int PositionY, std::vector<int> &PathfindingTrailX, std::vector<int> &PathfindingTrailY, std::shared_ptr<GameEntity> &EntityToMove)
{
    Pair src = std::make_pair(((int)Source.Position.y - CELL_SIZE / 2) / CELL_SIZE, ((int)Source.Position.x - CELL_SIZE / 2) / CELL_SIZE);
    Pair dest = std::make_pair(PositionX, PositionY);

    if (!isValid(dest.first, dest.second) || !isValid(src.first, src.second) || !isUnBlocked(MazeMap, dest.first, dest.second) || !isUnBlocked(MazeMap, src.first, src.second))
    {
        Source.Direction = Directions::None;
        src = std::make_pair(((int)Source.Position.y - CELL_SIZE / 2) / CELL_SIZE, ((int)Source.Position.x - CELL_SIZE / 2) / CELL_SIZE);
        dest = std::make_pair(PositionX, PositionY);
    }
    if (isDestination(src.first, src.second, dest) == true)
    {
        if (Source.Direction == Directions::Up)
        {
            Source.Position.y = dest.first * CELL_SIZE + CELL_SIZE / 2;
            Source.Direction = Directions::None;
        }
        if (Source.Direction == Directions::Down)
        {
            Source.Direction = Directions::None;
        }
        if (Source.Direction == Directions::Left)
        {
            Source.Position.x = dest.second * CELL_SIZE + CELL_SIZE / 2;
            Source.Direction = Directions::None;
        }
        if (Source.Direction == Directions::Right)
        {
            Source.Direction = Directions::None;
        }
    }
    else
    {
        AStarSearch(MazeMap, src, dest, PathfindingTrailX, PathfindingTrailY);

        int HalfSize = CELL_SIZE / 2;
        int NewX = Source.Position.x;
        int NewY = Source.Position.y;

        int UP_Y = (NewY - HalfSize - Source.Speed * DeltaTime) / CELL_SIZE;
        int UP_X = (NewX - HalfSize) / CELL_SIZE;

        int DOWN_Y = (NewY + HalfSize + Source.Speed * DeltaTime) / CELL_SIZE;
        int DOWN_X = (NewX - HalfSize) / CELL_SIZE;

        int LEFT_Y = (NewY - HalfSize) / CELL_SIZE;
        int LEFT_X = (NewX - HalfSize - Source.Speed * DeltaTime) / CELL_SIZE;

        int RIGHT_Y = (NewY - HalfSize) / CELL_SIZE;
        int RIGHT_X = (NewX + HalfSize + Source.Speed * DeltaTime) / CELL_SIZE;

        if (PathfindingTrailY[1] > (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE && PathfindingTrailX[1] == (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE)
        {
            Source.Direction = Directions::Right;
        }
        if (PathfindingTrailY[1] < (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE && PathfindingTrailX[1] == (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE)
        {
            Source.Direction = Directions::Left;
        }
        if (PathfindingTrailX[1] > (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE && PathfindingTrailY[1] == (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE)
        {
            Source.Direction = Directions::Down;
        }
        if (PathfindingTrailX[1] < (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE && PathfindingTrailY[1] == (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE)
        {
            Source.Direction = Directions::Up;
        }

        if (Source.Direction == Directions::Up)
        {
            if (MazeMap[UP_Y][UP_X] != 1 && PathfindingTrailX[1] <= (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE)
            {
                Source.Position.y -= Source.Speed * DeltaTime;
                PlayEnemyAnimation(Source, EntityToMove);
            }
            else
            {
                Source.Position.y = (UP_Y + 1) * CELL_SIZE + CELL_SIZE / 2;
                EntityToMove->SetTextureSourceX(2 * EntityToMove->GetTexture().width / EntityToMove->GetTextureFrames());
            }
        }
        if (Source.Direction == Directions::Down)
        {
            if (MazeMap[DOWN_Y][DOWN_X] != 1 && PathfindingTrailX[1] >= (Source.Position.y - CELL_SIZE / 2) / CELL_SIZE)
            {
                Source.Position.y += Source.Speed * DeltaTime;
                PlayEnemyAnimation(Source, EntityToMove);
            }
            else
            {
                Source.Position.y = (DOWN_Y - 1) * CELL_SIZE + CELL_SIZE / 2;
                EntityToMove->SetTextureSourceX(2 * EntityToMove->GetTexture().width / EntityToMove->GetTextureFrames());
            }
        }
        if (Source.Direction == Directions::Left)
        {
            if (MazeMap[LEFT_Y][LEFT_X] != 1 && MazeMap[LEFT_Y][LEFT_X] != 4 && PathfindingTrailY[1] <= (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE)
            {
                Source.Position.x -= Source.Speed * DeltaTime;
                PlayEnemyAnimation(Source, EntityToMove);
            }
            else
            {
                Source.Position.x = (LEFT_X + 1) * CELL_SIZE + CELL_SIZE / 2;
                EntityToMove->SetTextureSourceX(2 * EntityToMove->GetTexture().width / EntityToMove->GetTextureFrames());
            }
        }
        if (Source.Direction == Directions::Right)
        {
            if (MazeMap[RIGHT_Y][RIGHT_X] != 1 && MazeMap[RIGHT_Y][RIGHT_X] != 4 && PathfindingTrailY[1] >= (Source.Position.x - CELL_SIZE / 2) / CELL_SIZE)
            {
                Source.Position.x += Source.Speed * DeltaTime;
                PlayEnemyAnimation(Source, EntityToMove);
            }
            else
            {
                Source.Position.x = (RIGHT_X - 1) * CELL_SIZE + CELL_SIZE / 2;
                EntityToMove->SetTextureSourceX(2 * EntityToMove->GetTexture().width / EntityToMove->GetTextureFrames());
            }
        }

        EntityToMove->SetPosition(Source.Position.x, Source.Position.y);
    }

    PathfindingTrailX.clear();
    PathfindingTrailY.clear();
}

void GameLogic::Patrol(const float &DeltaTime, Character &PatrollingCharacter, std::vector<int> &PatrolLocationsX, std::vector<int> &PatrolLocationsY, std::vector<int> &PathfindingTrailX, std::vector<int> &PathfindingTrailY, std::shared_ptr<GameEntity> &EntityToMove)
{
    int PositionX = (PatrollingCharacter.Position.x - CELL_SIZE / 2) / CELL_SIZE;
    int PositionY = (PatrollingCharacter.Position.y - CELL_SIZE / 2) / CELL_SIZE;

    if (PatrollingCharacter.RouteNumber == 1)
    {
        if (PositionY == PatrolLocationsX.at(0) && PositionX == PatrolLocationsY.at(0))
        {
            PatrollingCharacter.RouteNumber = GetRandomValue(1, 4);
        }
        else
        {
            FallBackToBase(DeltaTime, PatrollingCharacter, PatrolLocationsX.at(0), PatrolLocationsY.at(0), PathfindingTrailX, PathfindingTrailY, EntityToMove);
        }
    }
    if (PatrollingCharacter.RouteNumber == 2)
    {
        if (PositionY == PatrolLocationsX.at(1) && PositionX == PatrolLocationsY.at(1))
        {
            PatrollingCharacter.RouteNumber = GetRandomValue(1, 4);
        }
        else
        {
            FallBackToBase(DeltaTime, PatrollingCharacter, PatrolLocationsX.at(1), PatrolLocationsY.at(1), PathfindingTrailX, PathfindingTrailY, EntityToMove);
        }
    }
    if (PatrollingCharacter.RouteNumber == 3)
    {
        if (PositionY == PatrolLocationsX.at(2) && PositionX == PatrolLocationsY.at(2))
        {
            PatrollingCharacter.RouteNumber = GetRandomValue(1, 4);
        }
        else
        {
            FallBackToBase(DeltaTime, PatrollingCharacter, PatrolLocationsX.at(2), PatrolLocationsY.at(2), PathfindingTrailX, PathfindingTrailY, EntityToMove);
        }
    }
    if (PatrollingCharacter.RouteNumber == 4)
    {
        if (PositionY == PatrolLocationsX.at(3) && PositionX == PatrolLocationsY.at(3))
        {
            PatrollingCharacter.RouteNumber = GetRandomValue(1, 4);
        }
        else
        {
            FallBackToBase(DeltaTime, PatrollingCharacter, PatrolLocationsX.at(3), PatrolLocationsY.at(3), PathfindingTrailX, PathfindingTrailY, EntityToMove);
        }
    }
}

void GameLogic::BlinkyMove(const float &DeltaTime) // Always follows Pacman's exact location, except when Pacman is in PowerUp state or he is at Scatter mode, then he patrols his territory //
{                                                  // Blinky will catch up in speed when 2/3 of the pellets are eaten // IMMORTAL - Cannot be killed //

    if (PelletCount <= NumberOfPellets / 3)
    {
        BlinkyCharacter.Speed = 114.0;
    }
    else
    {
        BlinkyCharacter.Speed = 96.0;
    }
    if (Pacman->State == State::PowerUp || Blinky->State == State::Scatter)
    {
        Patrol(DeltaTime, BlinkyCharacter, BlinkyPatrolLocationsX, BlinkyPatrolLocationsY, BlinkyPathfindingTrailX, BlinkyPathfindingTrailY, Blinky);
    }
    else if (Pacman->State == State::Nothing || Blinky->State == State::Chase)
    {
        EnemyMove(DeltaTime, BlinkyCharacter, PacmanCharacter, BlinkyPathfindingTrailX, BlinkyPathfindingTrailY, Blinky);
    }
}

void GameLogic::ClydeMove(const float &DeltaTime) // Only leaves the ghost house when 1/3 of the pellets are eaten //
{                                                 // If distance between him and pacman < 8 * cellsize || in Chase mode -> follows pacman's exact location, else patrols his corner //
    if (!ClydeCharacter.isEaten)
    {
        if (PelletCount <= std::round(NumberOfPellets / 3) * 2)
        {
            if (Vector2Distance({ClydeCharacter.Position.x, ClydeCharacter.Position.y}, {PacmanCharacter.Position.x, PacmanCharacter.Position.y}) >= 8 * CELL_SIZE)
            {
                if (Clyde->State == State::Scatter)
                {
                    Patrol(DeltaTime, ClydeCharacter, ClydePatrolLocationsX, ClydePatrolLocationsY, ClydePathfindingTrailX, ClydePathfindingTrailY, Clyde);
                }
                else if (Clyde->State == State::Chase)
                {
                    EnemyMove(DeltaTime, ClydeCharacter, PacmanCharacter, ClydePathfindingTrailX, ClydePathfindingTrailY, Clyde);
                }
            }
            else
            {
                if (Pacman->State == State::PowerUp || Clyde->State == State::Scatter)
                {
                    Patrol(DeltaTime, ClydeCharacter, ClydePatrolLocationsX, ClydePatrolLocationsY, ClydePathfindingTrailX, ClydePathfindingTrailY, Clyde);
                }
                else if (Pacman->State == State::Nothing || Blinky->State == State::Chase)
                {
                    EnemyMove(DeltaTime, ClydeCharacter, PacmanCharacter, ClydePathfindingTrailX, ClydePathfindingTrailY, Clyde);
                }
            }
        }
    }
    else
    {
        FallBackToBase(DeltaTime, ClydeCharacter, 12, 13, ClydePathfindingTrailX, ClydePathfindingTrailY, Clyde);
    }
}

void GameLogic::PinkyMove(const float &DeltaTime) // Leaves the ghost house immediately //
{                                                 // If distance between her and pacman is < 8 * cellsize || in Chase mode -> she follows pacman's location + 2 tiles ahead (if valid) if not, follow pacman exact loc //
    if (!PinkyCharacter.isEaten)
    {
        if (Vector2Distance({PinkyCharacter.Position.x, PinkyCharacter.Position.y}, {PacmanCharacter.Position.x, PacmanCharacter.Position.y}) >= 8 * CELL_SIZE)
        {
            if (Pinky->State == State::Scatter)
            {
                Patrol(DeltaTime, PinkyCharacter, PinkyPatrolLocationsX, PinkyPatrolLocationsY, PinkyPathfindingTrailX, PinkyPathfindingTrailY, Pinky);
            }
            else if (Pinky->State == State::Chase)
            {
                EnemyMove2StepsAheadPacman(DeltaTime, PinkyCharacter, PacmanCharacter, PinkyPathfindingTrailX, PinkyPathfindingTrailY, Pinky);
            }
        }
        else
        {
            if (Pacman->State == State::PowerUp || Pinky->State == State::Scatter)
            {
                Patrol(DeltaTime, PinkyCharacter, PinkyPatrolLocationsX, PinkyPatrolLocationsY, PinkyPathfindingTrailX, PinkyPathfindingTrailY, Pinky);
            }
            else if (Pacman->State == State::Nothing || Pinky->State == State::Chase)
            {
                EnemyMove2StepsAheadPacman(DeltaTime, PinkyCharacter, PacmanCharacter, PinkyPathfindingTrailX, PinkyPathfindingTrailY, Pinky);
            }
        }
    }
    else
    {
        FallBackToBase(DeltaTime, PinkyCharacter, 12, 12, PinkyPathfindingTrailX, PinkyPathfindingTrailY, Pinky);
    }
}

void GameLogic::InkyMove(const float &DeltaTime) // Only leaves the ghost house when Pacman has managed to consume at least 30 pellets //
{                                                // Shares Blinky-and-Pinky's attributes, If not scattering or terrified then he follows Pacman location + 2 tiles ahead(if valid) if not, follow pacman exact loc //
    if (!InkyCharacter.isEaten)
    {
        if (PelletCount <= (NumberOfPellets - 30))
        {
            if (Pacman->State == State::PowerUp || Inky->State == State::Scatter)
            {
                Patrol(DeltaTime, InkyCharacter, InkyPatrolLocationsX, InkyPatrolLocationsY, InkyPathfindingTrailX, InkyPathfindingTrailY, Inky);
            }
            else if (Pacman->State == State::Nothing || Inky->State == State::Chase)
            {
                EnemyMove2StepsAheadPacman(DeltaTime, InkyCharacter, PacmanCharacter, InkyPathfindingTrailX, InkyPathfindingTrailY, Inky);
            }
        }
    }
    else
    {
        FallBackToBase(DeltaTime, InkyCharacter, 12, 11, InkyPathfindingTrailX, InkyPathfindingTrailY, Inky);
    }
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
    GateTexture = LoadTexture("./Assets/Gate.png");

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
                Wall->SetWidthScale(0.048f);
                Wall->SetHeightScale(0.048f);
                Wall->CellType = CellType::Wall;
                GameEntities.emplace_back(Wall);
            }
            else if (MazeMap[i][j] == 2)
            {
                std::shared_ptr<GameEntity> Food = std::make_shared<GameEntity>("Food" + std::to_string(i));
                Food->AddPositionComponent();
                Food->AddSprite2DComponentWithTexture(FoodTexture);
                Food->SetPosition(j * CELL_SIZE + CELL_SIZE / 2, i * CELL_SIZE + CELL_SIZE / 2);
                Food->SetWidthScale(0.25f);
                Food->SetHeightScale(0.25f);
                Food->CellType = CellType::Food;
                Food->SetTextureColor(ORANGE);
                GameEntities.emplace_back(Food);
                PelletCount++;
            }
            else if (MazeMap[i][j] == 3)
            {
                std::shared_ptr<GameEntity> PowerUp = std::make_shared<GameEntity>("PowerUp" + std::to_string(i));
                PowerUp->AddPositionComponent();
                PowerUp->AddSprite2DComponentWithTexture(FoodTexture);
                PowerUp->SetPosition(j * CELL_SIZE + CELL_SIZE / 2, i * CELL_SIZE + CELL_SIZE / 2);
                PowerUp->SetWidthScale(0.5f);
                PowerUp->SetHeightScale(0.5f);
                PowerUp->CellType = CellType::PowerUp;
                PowerUp->SetTextureColor(RED);
                GameEntities.emplace_back(PowerUp);
                PelletCount++;
            }
            else if (MazeMap[i][j] == 4)
            {
                std::shared_ptr<GameEntity> GhostHouseGate = std::make_shared<GameEntity>("GhostHouseGate");
                GhostHouseGate->AddPositionComponent();
                GhostHouseGate->AddSprite2DComponentWithTexture(GateTexture);
                GhostHouseGate->SetPosition(j * CELL_SIZE + CELL_SIZE / 2, i * CELL_SIZE + 1);
                GhostHouseGate->SetWidthScale(0.5f);
                GhostHouseGate->SetHeightScale(0.5f);
                GhostHouseGate->SetTextureColor(BLUE);
                GameEntities.emplace_back(GhostHouseGate);
            }
        }
    }
}

void GameLogic::SetStartingPositions()
{
    PacmanCharacter.Position = {12 * CELL_SIZE + CELL_SIZE / 2, 18 * CELL_SIZE + CELL_SIZE / 2};
    BlinkyCharacter.Position = {12 * CELL_SIZE + CELL_SIZE / 2, 10 * CELL_SIZE + CELL_SIZE / 2};
    ClydeCharacter.Position = {13 * CELL_SIZE + CELL_SIZE / 2, 12 * CELL_SIZE + CELL_SIZE / 2};
    InkyCharacter.Position = {11 * CELL_SIZE + CELL_SIZE / 2, 12 * CELL_SIZE + CELL_SIZE / 2};
    PinkyCharacter.Position = {12 * CELL_SIZE + CELL_SIZE / 2, 12 * CELL_SIZE + CELL_SIZE / 2};
}

void GameLogic::InitCharacter(std::shared_ptr<GameEntity> &Entity, std::vector<std::shared_ptr<GameEntity>> &EntityVector, const float PosX, const float PosY, const char *FilePath, const float Rotation, const float WidthScale, const float HeightScale, const int Frames, const float SourceX, Color TextureColor)
{
    Entity->AddPositionComponent();
    Entity->AddVelocityComponent();
    Entity->AddSprite2DComponent(FilePath);
    Entity->SetPosition(PosX, PosY);
    Entity->SetRotation(Rotation);
    Entity->SetWidthScale(WidthScale);
    Entity->SetHeightScale(HeightScale);
    Entity->SetTextureFrames(Frames);
    Entity->SetTextureSourceX(SourceX);
    Entity->SetTextureColor(TextureColor);
    EntityVector.emplace_back(Entity);
    GameEntities.emplace_back(Entity);
}

// A* Pathfinding algorithm //

bool GameLogic::isValid(int row, int col)
{
    return (row >= 0) && (row < CELL_ROWS) && (col >= 0) && (col < CELL_COLS);
}

bool GameLogic::isUnBlocked(int grid[CELL_ROWS][CELL_COLS], int row, int col)
{
    if (grid[row][col] != 1)
        return true;
    else
        return false;
}

bool GameLogic::isDestination(int row, int col, Pair dest)
{
    if (row == dest.first && col == dest.second)
        return true;
    else
        return false;
}

double GameLogic::CalculateHValue(int row, int col, Pair dest)
{
    return (abs(row - dest.first) + (abs(col - dest.second)));
}

void GameLogic::TracePath(Cell CellDetails[CELL_ROWS][CELL_COLS], Pair dest, std::vector<int> &PathfindingTrailX, std::vector<int> &PathfindingTrailY)
{
    // printf("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;

    std::stack<Pair> Path;

    while (!(CellDetails[row][col].Parent_i == row && CellDetails[row][col].Parent_j == col))
    {
        Path.push(std::make_pair(row, col));
        int Temp_row = CellDetails[row][col].Parent_i;
        int Temp_col = CellDetails[row][col].Parent_j;
        row = Temp_row;
        col = Temp_col;
    }

    Path.push(std::make_pair(row, col));

    while (!Path.empty())
    {
        std::pair<int, int> p = Path.top();
        Path.pop();
        // printf("-> (%i, %i) ", p.first, p.second);
        PathfindingTrailX.emplace_back(p.first);
        PathfindingTrailY.emplace_back(p.second);
    }
    return;
}

void GameLogic::AStarSearch(int grid[CELL_ROWS][CELL_COLS], Pair src, Pair dest, std::vector<int> &PathfindingTrailX, std::vector<int> &PathfindingTrailY)
{
    if (isValid(src.first, src.second) == false)
    {
        printf("Source is invalid \n");
        return;
    }
    if (isValid(dest.first, dest.second) == false)
    {
        printf("Destination is invalid \n");
        return;
    }
    if (isUnBlocked(grid, src.first, src.second) == false || isUnBlocked(grid, dest.first, dest.second) == false)
    {
        printf("Source or the destination is blocked\n");
        return;
    }
    if (isDestination(src.first, src.second, dest) == true)
    {
        // printf("We are already at the destination\n");
        return;
    }

    bool ClosedList[CELL_ROWS][CELL_COLS];
    memset(ClosedList, false, sizeof(ClosedList));

    Cell CellDetails[CELL_ROWS][CELL_COLS];

    int i = 0;
    int j = 0;

    for (i = 0; i < CELL_ROWS; i++)
    {
        for (j = 0; j < CELL_COLS; j++)
        {
            CellDetails[i][j].f = FLT_MAX;
            CellDetails[i][j].g = FLT_MAX;
            CellDetails[i][j].h = FLT_MAX;
            CellDetails[i][j].Parent_i = -1;
            CellDetails[i][j].Parent_j = -1;
        }
    }

    i = src.first;
    j = src.second;
    CellDetails[i][j].f = 0.0;
    CellDetails[i][j].g = 0.0;
    CellDetails[i][j].h = 0.0;
    CellDetails[i][j].Parent_i = i;
    CellDetails[i][j].Parent_j = j;

    std::set<pPair> OpenList;
    OpenList.insert(std::make_pair(0.0, std::make_pair(i, j)));
    bool FoundDest = false;

    while (!OpenList.empty())
    {
        pPair p = *OpenList.begin();

        OpenList.erase(OpenList.begin());

        i = p.second.first;
        j = p.second.second;
        ClosedList[i][j] = true;

        // Generating 4 successor of this cell
        //------------------------------------
        //                  N
        //                  |
        //                  |
        //                  |
        //        W--------CELL--------E
        //                  |
        //                  |
        //                  |
        //                  S
        //------------------------------------
        //        CELL-> Popped Cell (i, j)
        //        N-> North (i-1, j)
        //        S-> South (i+1, j)
        //        E-> East (i, j+1)
        //        W-> West (i, j-1)
        //------------------------------------

        double GNew = 0.0;
        double HNew = 0.0;
        double FNew = 0.0;

        //----------------1st Successor (North) ---------------- //
        if (isValid(i - 1, j) == true)
        {
            if (isDestination(i - 1, j, dest) == true)
            {
                CellDetails[i - 1][j].Parent_i = i;
                CellDetails[i - 1][j].Parent_j = j;
                // printf("The destination cell is found\n");
                TracePath(CellDetails, dest, PathfindingTrailX, PathfindingTrailY);
                FoundDest = true;
                return;
            }
            else if (ClosedList[i - 1][j] == false && isUnBlocked(grid, i - 1, j) == true)
            {
                GNew = CellDetails[i][j].g + 1.0;
                HNew = CalculateHValue(i - 1, j, dest);
                FNew = GNew + HNew;

                if (CellDetails[i - 1][j].f == FLT_MAX || CellDetails[i - 1][j].f > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, std::make_pair(i - 1, j)));

                    CellDetails[i - 1][j].f = FNew;
                    CellDetails[i - 1][j].g = GNew;
                    CellDetails[i - 1][j].h = HNew;
                    CellDetails[i - 1][j].Parent_i = i;
                    CellDetails[i - 1][j].Parent_j = j;
                }
            }
        }

        //----------------2nd Successor (South) ---------------- //
        if (isValid(i + 1, j) == true)
        {
            if (isDestination(i + 1, j, dest) == true)
            {
                CellDetails[i + 1][j].Parent_i = i;
                CellDetails[i + 1][j].Parent_j = j;
                // printf("The destination cell is found\n");
                TracePath(CellDetails, dest, PathfindingTrailX, PathfindingTrailY);
                FoundDest = true;
                return;
            }
            else if (ClosedList[i + 1][j] == false && isUnBlocked(grid, i + 1, j) == true)
            {
                GNew = CellDetails[i][j].g + 1.0;
                HNew = CalculateHValue(i + 1, j, dest);
                FNew = GNew + HNew;

                if (CellDetails[i + 1][j].f == FLT_MAX || CellDetails[i + 1][j].f > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, std::make_pair(i + 1, j)));

                    CellDetails[i + 1][j].f = FNew;
                    CellDetails[i + 1][j].g = GNew;
                    CellDetails[i + 1][j].h = HNew;
                    CellDetails[i + 1][j].Parent_i = i;
                    CellDetails[i + 1][j].Parent_j = j;
                }
            }
        }

        //----------------3rd Successor (East) ---------------- //
        if (isValid(i, j + 1) == true)
        {
            if (isDestination(i, j + 1, dest) == true)
            {
                CellDetails[i][j + 1].Parent_i = i;
                CellDetails[i][j + 1].Parent_j = j;
                // printf("The destination cell is found\n");
                TracePath(CellDetails, dest, PathfindingTrailX, PathfindingTrailY);
                FoundDest = true;
                return;
            }
            else if (ClosedList[i][j + 1] == false && isUnBlocked(grid, i, j + 1) == true)
            {
                GNew = CellDetails[i][j].g + 1.0;
                HNew = CalculateHValue(i, j + 1, dest);
                FNew = GNew + HNew;

                if (CellDetails[i][j + 1].f == FLT_MAX || CellDetails[i][j + 1].f > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, std::make_pair(i, j + 1)));

                    CellDetails[i][j + 1].f = FNew;
                    CellDetails[i][j + 1].g = GNew;
                    CellDetails[i][j + 1].h = HNew;
                    CellDetails[i][j + 1].Parent_i = i;
                    CellDetails[i][j + 1].Parent_j = j;
                }
            }
        }

        //----------------4th Successor (West) ---------------- //
        if (isValid(i, j - 1) == true)
        {
            if (isDestination(i, j - 1, dest) == true)
            {
                CellDetails[i][j - 1].Parent_i = i;
                CellDetails[i][j - 1].Parent_j = j;
                // printf("The destination cell is found\n");
                TracePath(CellDetails, dest, PathfindingTrailX, PathfindingTrailY);
                FoundDest = true;
                return;
            }
            else if (ClosedList[i][j - 1] == false && isUnBlocked(grid, i, j - 1) == true)
            {
                GNew = CellDetails[i][j].g + 1.0;
                HNew = CalculateHValue(i, j - 1, dest);
                FNew = GNew + HNew;

                if (CellDetails[i][j - 1].f == FLT_MAX || CellDetails[i][j - 1].f > FNew)
                {
                    OpenList.insert(std::make_pair(FNew, std::make_pair(i, j - 1)));

                    CellDetails[i][j - 1].f = FNew;
                    CellDetails[i][j - 1].g = GNew;
                    CellDetails[i][j - 1].h = HNew;
                    CellDetails[i][j - 1].Parent_i = i;
                    CellDetails[i][j - 1].Parent_j = j;
                }
            }
        }
    }
    if (FoundDest == false)
    {
        printf("Failed to find the Destination Cell\n");
    }

    return;
}