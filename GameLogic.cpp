#include "GameLogic.h"
#include <GameEntity.h>
#include <raylib.h>
#include <raymath.h>

static const int CELL_ROWS{21};
static const int CELL_COLS{21};
static const int CELL_SIZE{40};

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
        1, 1, 2, 1, 1, 2, 1, 2, 1, 2, 2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 1,
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
    PacmanPos = {420, 620};
    Pacman->SetPosition(PacmanPos.x, PacmanPos.y);
    Pacman->SetRotation(0.f);
    Pacman->SetScale(0.065f);
    gameEntities.push_back(Pacman);

    Blinky->AddPositionComponent();
    Blinky->AddVelocityComponent();
    Blinky->AddSprite2DComponent("./Assets/Blinky.png");
    BlinkyPos = {220, 220};
    Blinky->SetPosition(BlinkyPos.x, BlinkyPos.y);
    Blinky->SetRotation(0.f);
    Blinky->SetScale(0.1f);
    gameEntities.push_back(Blinky);

    WallTexture = LoadTexture("./Assets/Wall.png");
    FoodTexture = LoadTexture("./Assets/Food.png");

    for (int i{}; i < CELL_ROWS; i++)
    {
        for (int j{}; j < CELL_COLS; j++)
        {
            if (MazeMap[i][j] == 1)
            {
                GameEntity *Wall = new GameEntity();
                Wall->AddPositionComponent();
                Wall->AddSprite2DComponentWithTexture(WallTexture);
                Wall->SetPosition(j * CELL_SIZE + CELL_SIZE / 2, i * CELL_SIZE + CELL_SIZE / 2);
                Wall->SetScale(0.085f);
                WallEntities.push_back(Wall);
            }
            if (MazeMap[i][j] == 2)
            {
                GameEntity *Food = new GameEntity();
                Food->AddPositionComponent();
                Food->AddSprite2DComponentWithTexture(FoodTexture);
                Food->SetPosition(j * CELL_SIZE + CELL_SIZE / 2, i * CELL_SIZE + CELL_SIZE / 2);
                Food->SetScale(0.025f);
                FoodEntities.push_back(Food);
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

    for (long long unsigned int i{}; i < WallEntities.size(); i++)
    {
        delete WallEntities[i];
    }
    for (long long unsigned int i{}; i < FoodEntities.size(); i++)
    {
        delete FoodEntities[i];
    }
    for (long long unsigned int i{}; i < gameEntities.size(); i++)
    {
        delete gameEntities[i];
    }
}

void GameLogic::Render()
{
    for (long long unsigned int i{}; i < WallEntities.size(); i++)
    {
        WallEntities[i]->Render();
    }
    for (long long unsigned int i{}; i < FoodEntities.size(); i++)
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
    for (long long unsigned int i{}; i < gameEntities.size(); i++)
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
    Timer(5);
    if (!StartDelay)
    {
        if (!Pacman->IsDead)
        {
            PacmanMove(DeltaTime);
        }

        BlinkyMove(DeltaTime);
    }
}

void GameLogic::Timer(double count)
{
    double currentTime = GetTime();
    if (currentTime < count)
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

    if (IsKeyDown(KEY_W) && PacmanPos.y - Pacman->GetTexture().height * Pacman->GetScale() / 2 >= 0)
    {
        Pacman->SetRotation(270.f);
        PacmanPos.y -= PacmanUpVelocity;
        Pacman->SetPosition(PacmanPos.x, PacmanPos.y);
    }
    if (IsKeyDown(KEY_S) && PacmanPos.y + Pacman->GetTexture().height * Pacman->GetScale() / 2 <= GetScreenHeight())
    {
        Pacman->SetRotation(90.f);
        PacmanPos.y += PacmanDownVelocity;
        Pacman->SetPosition(PacmanPos.x, PacmanPos.y);
    }
    if (IsKeyDown(KEY_A) && PacmanPos.x - Pacman->GetTexture().width * Pacman->GetScale() / 2 >= 0)
    {
        Pacman->SetRotation(180.f);
        PacmanPos.x -= PacmanLeftVelocity;
        Pacman->SetPosition(PacmanPos.x, PacmanPos.y);
    }
    if (IsKeyDown(KEY_D) && PacmanPos.x + Pacman->GetTexture().width * Pacman->GetScale() / 2 <= GetScreenWidth())
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
    for (long long unsigned int i{}; i < WallEntities.size(); i++)
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

    for (long long unsigned int i{}; i < WallEntities.size(); i++)
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
