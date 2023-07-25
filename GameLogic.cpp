#include "GameLogic.h"
#include <GameEntity.h>
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <iostream>

static const int CELL_ROWS = 20;
static const int CELL_COLS = 21;
static const int CELL_SIZE = 40;

std::shared_ptr<GameEntity> Pacman = std::make_shared<GameEntity>("Pacman");
std::shared_ptr<GameEntity> Blinky = std::make_shared<GameEntity>("Blinky");
// GameEntity *Clyde = new GameEntity();
// GameEntity *Inky = new GameEntity();
// GameEntity *Pinky = new GameEntity();

int MazeMap[CELL_ROWS][CELL_COLS] =
    {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1,
        1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1,
        1, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 1,
        0, 0, 0, 0, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 0, 0, 0, 0,
        0, 0, 0, 0, 1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 2, 1, 0, 0, 0, 0,
        1, 1, 1, 1, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2,
        1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1,
        1, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 1,
        1, 1, 2, 1, 1, 2, 1, 2, 1, 2, 0, 2, 1, 2, 1, 2, 1, 1, 2, 1, 1,
        1, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 1,
        1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

GameLogic::GameLogic()
{
    CellRows = CELL_ROWS;
    CellCols = CELL_COLS;
    CellSize = CELL_SIZE;

    Pacman->AddPositionComponent();
    Pacman->AddVelocityComponent();
    Pacman->AddSprite2DComponent("./Assets/Pacman.png");
    PacmanPos = {420.f, 620.f};
    Pacman->SetPosition(PacmanPos.x, PacmanPos.y);
    Pacman->SetRotation(0.f);
    Pacman->SetScale(0.065f);
    gameEntities.emplace_back(Pacman);

    Blinky->AddPositionComponent();
    Blinky->AddVelocityComponent();
    Blinky->AddSprite2DComponent("./Assets/Blinky.png");
    BlinkyPos = {220.f, 220.f};
    Blinky->SetPosition(BlinkyPos.x, BlinkyPos.y);
    Blinky->SetRotation(0.f);
    Blinky->SetScale(0.1f);
    gameEntities.emplace_back(Blinky);

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
                Wall->CellType = CellType::CT_Wall;
                WallEntities.emplace_back(Wall);
            }
            if (MazeMap[i][j] == 2)
            {
                std::shared_ptr<GameEntity> Food = std::make_shared<GameEntity>("Food" + std::to_string(i));
                Food->AddPositionComponent();
                Food->AddSprite2DComponentWithTexture(FoodTexture);
                Food->SetPosition(j * CELL_SIZE + CELL_SIZE / 2, i * CELL_SIZE + CELL_SIZE / 2);
                Food->SetScale(0.025f);
                Food->CellType = CellType::CT_Food;
                FoodEntities.emplace_back(Food);
            }
        }
    }

    InitAudioDevice();
    CreditSound = LoadSound("./Sounds/credit.wav");
    StartSound = LoadSound("./Sounds/game_start.wav");
    PacmanDeadSound = LoadSound("./Sounds/death_1.wav");
}

GameLogic::~GameLogic()
{
    UnloadSound(CreditSound);
    UnloadSound(StartSound);
    UnloadSound(PacmanDeadSound);
    CloseAudioDevice();
    UnloadTexture(WallTexture);
    UnloadTexture(FoodTexture);
}

void GameLogic::Render()
{
    for (int i = 0; i < (int)WallEntities.size(); i++)
    {
        WallEntities[i]->Render();
    }
    for (int i = 0; i < (int)FoodEntities.size(); i++)
    {
        Rectangle PacmanRec = {Pacman->GetPosition().x - Pacman->GetTexture().width * Pacman->GetScale() / 2, Pacman->GetPosition().y - Pacman->GetTexture().height * Pacman->GetScale() / 2, Pacman->GetTexture().width * Pacman->GetScale(), Pacman->GetTexture().height * Pacman->GetScale()};
        Rectangle FoodRec = {FoodEntities[i]->GetPosition().x - FoodEntities[i]->GetTexture().width * FoodEntities[i]->GetScale() / 2, FoodEntities[i]->GetPosition().y - FoodEntities[i]->GetTexture().height * FoodEntities[i]->GetScale() / 2, FoodEntities[i]->GetTexture().width * FoodEntities[i]->GetScale(), FoodEntities[i]->GetTexture().height * FoodEntities[i]->GetScale()};
        // DrawRectangleRec(FoodRec, RED);
        // DrawRectangleRec(PacmanRec, RED);

        if (CheckCollisionRecs(PacmanRec, FoodRec))
        {
            FoodEntities.erase(FoodEntities.begin() + i);
            PlaySound(CreditSound);
            Score++;
        }
        else
        {
            FoodEntities[i]->Render();
        }
    }
    for (int i = 0; i < (int)gameEntities.size(); i++)
    {
        gameEntities[i]->Render();
    }
    ShowScore();
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
    StartTimer(6.0);
    if (!StartDelay)
    {
        if (!Pacman->IsDead)
        {
            PacmanMove(DeltaTime);
        }

        BlinkyMove(DeltaTime);
    }

    DrawText("PAC", 20, 292, 60, YELLOW);
    DrawText("MAN", GetScreenWidth() - 140, 292, 60, YELLOW);
}

void GameLogic::StartTimer(double seconds)
{
    double currentTime = GetTime();
    if (currentTime < seconds)
    {
        StartDelay = true;
    }
    else
    {
        StartDelay = false;
    }
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

void GameLogic::PacmanMove(float DeltaTime)
{
    InitializePacmanVelocity(DeltaTime);
    PacmanCollisionCheck();

    switch ((GetKeyPressed()))
    {
    case KEY_W:
        PacmanDirection = Directions::Up;
        break;
    case KEY_S:
        PacmanDirection = Directions::Down;
        break;
    case KEY_A:
        PacmanDirection = Directions::Left;
        break;
    case KEY_D:
        PacmanDirection = Directions::Right;
        break;
    default:
        break;
    }

    if (PacmanPos.y - Pacman->GetTexture().height * Pacman->GetScale() / 2 >= 0 && PacmanDirection == Directions::Up)
    {
        Pacman->SetRotation(270.f);
        PacmanPos.y -= PacmanUpVelocity;
        Pacman->SetPosition(PacmanPos.x, PacmanPos.y);
    }
    if (PacmanPos.y + Pacman->GetTexture().height * Pacman->GetScale() / 2 <= GetScreenHeight() && PacmanDirection == Directions::Down)
    {
        Pacman->SetRotation(90.f);
        PacmanPos.y += PacmanDownVelocity;
        Pacman->SetPosition(PacmanPos.x, PacmanPos.y);
    }
    if (PacmanPos.x - Pacman->GetTexture().width * Pacman->GetScale() / 2 >= 0 && PacmanDirection == Directions::Left)
    {
        Pacman->SetRotation(180.f);
        PacmanPos.x -= PacmanLeftVelocity;
        Pacman->SetPosition(PacmanPos.x, PacmanPos.y);
    }
    if (PacmanPos.x + Pacman->GetTexture().width * Pacman->GetScale() / 2 <= GetScreenWidth() && PacmanDirection == Directions::Right)
    {
        Pacman->SetRotation(0.f);
        PacmanPos.x += PacmanRightVelocity;
        Pacman->SetPosition(PacmanPos.x, PacmanPos.y);
    }

    SecretDoor();
}

void GameLogic::InitializePacmanVelocity(float DeltaTime)
{
    PacmanUpVelocity = DeltaTime * PacmanSpeed;
    PacmanDownVelocity = DeltaTime * PacmanSpeed;
    PacmanLeftVelocity = DeltaTime * PacmanSpeed;
    PacmanRightVelocity = DeltaTime * PacmanSpeed;
}

void GameLogic::PacmanCollisionCheck()
{
    for (int i{}; i < (int)WallEntities.size(); i++)
    {
        if (CheckCollisionPointLine({Pacman->GetPosition().x, Pacman->GetPosition().y - Pacman->GetTexture().height * Pacman->GetScale() / 2}, {WallEntities[i]->GetPosition().x - WallEntities[i]->GetTexture().width * WallEntities[i]->GetScale() / 2 - Pacman->GetTexture().width * Pacman->GetScale() / 2 + 1, WallEntities[i]->GetPosition().y + WallEntities[i]->GetTexture().height * WallEntities[i]->GetScale() / 2}, {WallEntities[i]->GetPosition().x + WallEntities[i]->GetTexture().width * WallEntities[i]->GetScale() / 2 + Pacman->GetTexture().width * Pacman->GetScale() / 2 - 1, WallEntities[i]->GetPosition().y + WallEntities[i]->GetTexture().height * WallEntities[i]->GetScale() / 2}, 1))
        {
            PacmanUpVelocity = 0.f;
        }
        if (CheckCollisionPointLine({Pacman->GetPosition().x, Pacman->GetPosition().y + Pacman->GetTexture().height * Pacman->GetScale() / 2}, {WallEntities[i]->GetPosition().x - WallEntities[i]->GetTexture().width * WallEntities[i]->GetScale() / 2 - Pacman->GetTexture().width * Pacman->GetScale() / 2 + 1, WallEntities[i]->GetPosition().y - WallEntities[i]->GetTexture().height * WallEntities[i]->GetScale() / 2}, {WallEntities[i]->GetPosition().x + WallEntities[i]->GetTexture().width * WallEntities[i]->GetScale() / 2 + Pacman->GetTexture().width * Pacman->GetScale() / 2 - 1, WallEntities[i]->GetPosition().y - WallEntities[i]->GetTexture().height * WallEntities[i]->GetScale() / 2}, 1))
        {
            PacmanDownVelocity = 0.f;
        }
        if (CheckCollisionPointLine({Pacman->GetPosition().x + Pacman->GetTexture().width * Pacman->GetScale() / 2, Pacman->GetPosition().y}, {WallEntities[i]->GetPosition().x - WallEntities[i]->GetTexture().width * WallEntities[i]->GetScale() / 2, WallEntities[i]->GetPosition().y - WallEntities[i]->GetTexture().height * WallEntities[i]->GetScale() / 2 - Pacman->GetTexture().height * Pacman->GetScale() / 2 + 1}, {WallEntities[i]->GetPosition().x - WallEntities[i]->GetTexture().width * WallEntities[i]->GetScale() / 2, WallEntities[i]->GetPosition().y + WallEntities[i]->GetTexture().height * WallEntities[i]->GetScale() / 2 + Pacman->GetTexture().height * Pacman->GetScale() / 2 - 1}, 1))
        {
            PacmanRightVelocity = 0.f;
        }
        if (CheckCollisionPointLine({Pacman->GetPosition().x - Pacman->GetTexture().width * Pacman->GetScale() / 2, Pacman->GetPosition().y}, {WallEntities[i]->GetPosition().x + WallEntities[i]->GetTexture().width * WallEntities[i]->GetScale() / 2, WallEntities[i]->GetPosition().y - WallEntities[i]->GetTexture().height * WallEntities[i]->GetScale() / 2 - Pacman->GetTexture().height * Pacman->GetScale() / 2 + 1}, {WallEntities[i]->GetPosition().x + WallEntities[i]->GetTexture().width * WallEntities[i]->GetScale() / 2, WallEntities[i]->GetPosition().y + WallEntities[i]->GetTexture().height * WallEntities[i]->GetScale() / 2 + Pacman->GetTexture().height * Pacman->GetScale() / 2 - 1}, 1))
        {
            PacmanLeftVelocity = 0.f;
        }
        // DrawCircle(Pacman->GetPosition().x + Pacman->GetTexture().width * Pacman->GetScale() / 2, Pacman->GetPosition().y, 2, RED);
    }

    Rectangle PacmanRec = {Pacman->GetPosition().x - Pacman->GetTexture().width * Pacman->GetScale() / 2, Pacman->GetPosition().y - Pacman->GetTexture().height * Pacman->GetScale() / 2, Pacman->GetTexture().width * Pacman->GetScale(), Pacman->GetTexture().height * Pacman->GetScale()};
    Rectangle BlinkyRec = {Blinky->GetPosition().x - Blinky->GetTexture().width * Blinky->GetScale() / 2, Blinky->GetPosition().y - Blinky->GetTexture().height * Blinky->GetScale() / 2, Blinky->GetTexture().width * Blinky->GetScale(), Blinky->GetTexture().height * Blinky->GetScale()};
    if (CheckCollisionRecs(PacmanRec, BlinkyRec))
    {
        Pacman->IsDead = true;
        PlaySound(PacmanDeadSound);
    }
}

void GameLogic::SecretDoor()
{
    if (Pacman->GetPosition().x + Pacman->GetTexture().width * Pacman->GetScale() / 2 >= GetScreenWidth() && Pacman->GetPosition().y >= 400.f)
    {
        PacmanPos.x = 0.f + Pacman->GetTexture().width * Pacman->GetScale() / 2;
        PacmanPos.x += PacmanRightVelocity;
        Pacman->SetPosition(PacmanPos.x, Pacman->GetPosition().y);
    }
    if (Pacman->GetPosition().x - Pacman->GetTexture().width * Pacman->GetScale() / 2 <= 0 && Pacman->GetPosition().y >= 400.f)
    {
        PacmanPos.x = GetScreenWidth() - Pacman->GetTexture().width * Pacman->GetScale() / 2 - 2;
        PacmanPos.x += PacmanLeftVelocity;
        Pacman->SetPosition(PacmanPos.x, Pacman->GetPosition().y);
    }
}

void GameLogic::BlinkyMove(float DeltaTime)
{
    BlinkyUpVelocity = DeltaTime * BlinkySpeed;
    BlinkyDownVelocity = DeltaTime * BlinkySpeed;
    BlinkyLeftVelocity = DeltaTime * BlinkySpeed;
    BlinkyRightVelocity = DeltaTime * BlinkySpeed;

    for (int i{}; i < (int)WallEntities.size(); i++)
    {
        if (CheckCollisionPointLine({Blinky->GetPosition().x, Blinky->GetPosition().y - Blinky->GetTexture().height * Blinky->GetScale() / 2}, {WallEntities[i]->GetPosition().x - WallEntities[i]->GetTexture().width * WallEntities[i]->GetScale() / 2 - Blinky->GetTexture().width * Blinky->GetScale() / 2 + 1, WallEntities[i]->GetPosition().y + WallEntities[i]->GetTexture().height * WallEntities[i]->GetScale() / 2}, {WallEntities[i]->GetPosition().x + WallEntities[i]->GetTexture().width * WallEntities[i]->GetScale() / 2 + Blinky->GetTexture().width * Blinky->GetScale() / 2 - 1, WallEntities[i]->GetPosition().y + WallEntities[i]->GetTexture().height * WallEntities[i]->GetScale() / 2}, 1))
        {
            BlinkyUpVelocity = 0.f;
        }
        if (CheckCollisionPointLine({Blinky->GetPosition().x, Blinky->GetPosition().y + Blinky->GetTexture().height * Blinky->GetScale() / 2}, {WallEntities[i]->GetPosition().x - WallEntities[i]->GetTexture().width * WallEntities[i]->GetScale() / 2 - Blinky->GetTexture().width * Blinky->GetScale() / 2 + 1, WallEntities[i]->GetPosition().y - WallEntities[i]->GetTexture().height * WallEntities[i]->GetScale() / 2}, {WallEntities[i]->GetPosition().x + WallEntities[i]->GetTexture().width * WallEntities[i]->GetScale() / 2 + Blinky->GetTexture().width * Blinky->GetScale() / 2 - 1, WallEntities[i]->GetPosition().y - WallEntities[i]->GetTexture().height * WallEntities[i]->GetScale() / 2}, 1))
        {
            BlinkyDownVelocity = 0.f;
        }
        if (CheckCollisionPointLine({Blinky->GetPosition().x + Blinky->GetTexture().width * Blinky->GetScale() / 2, Blinky->GetPosition().y}, {WallEntities[i]->GetPosition().x - WallEntities[i]->GetTexture().width * WallEntities[i]->GetScale() / 2, WallEntities[i]->GetPosition().y - WallEntities[i]->GetTexture().height * WallEntities[i]->GetScale() / 2 - Blinky->GetTexture().height * Blinky->GetScale() / 2 + 1}, {WallEntities[i]->GetPosition().x - WallEntities[i]->GetTexture().width * WallEntities[i]->GetScale() / 2, WallEntities[i]->GetPosition().y + WallEntities[i]->GetTexture().height * WallEntities[i]->GetScale() / 2 + Blinky->GetTexture().height * Blinky->GetScale() / 2 - 1}, 1))
        {
            BlinkyRightVelocity = 0.f;
        }
        if (CheckCollisionPointLine({Blinky->GetPosition().x - Blinky->GetTexture().width * Blinky->GetScale() / 2, Blinky->GetPosition().y}, {WallEntities[i]->GetPosition().x + WallEntities[i]->GetTexture().width * WallEntities[i]->GetScale() / 2, WallEntities[i]->GetPosition().y - WallEntities[i]->GetTexture().height * WallEntities[i]->GetScale() / 2 - Blinky->GetTexture().height * Blinky->GetScale() / 2 + 1}, {WallEntities[i]->GetPosition().x + WallEntities[i]->GetTexture().width * WallEntities[i]->GetScale() / 2, WallEntities[i]->GetPosition().y + WallEntities[i]->GetTexture().height * WallEntities[i]->GetScale() / 2 + Blinky->GetTexture().height * Blinky->GetScale() / 2 - 1}, 1))
        {
            BlinkyLeftVelocity = 0.f;
        }
        // DrawCircle(Blinky->GetPosition().x + Blinky->GetTexture().width * Blinky->GetScale() / 2, Blinky->GetPosition().y, 2, RED);
    }
    if (PacmanPos.x >= BlinkyPos.x)
    {
        BlinkyPos.x += BlinkyRightVelocity;
        Blinky->SetPosition(BlinkyPos.x, BlinkyPos.y);
    }
    if (PacmanPos.y >= BlinkyPos.y)
    {
        BlinkyPos.y += BlinkyDownVelocity;
        Blinky->SetPosition(BlinkyPos.x, BlinkyPos.y);
    }
    if (PacmanPos.x <= BlinkyPos.x)
    {
        BlinkyPos.x -= BlinkyLeftVelocity;
        Blinky->SetPosition(BlinkyPos.x, BlinkyPos.y);
    }
    if (PacmanPos.y <= BlinkyPos.y)
    {
        BlinkyPos.y -= BlinkyUpVelocity;
        Blinky->SetPosition(BlinkyPos.x, BlinkyPos.y);
    }
}
