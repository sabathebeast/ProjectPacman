#include "GameLogic.h"
#include <GameEntity.h>
#include <raylib.h>
#include <raymath.h>
#include <string>

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
        1, 1, 1, 1, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 1, 1, 1, 1,
        2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2,
        1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 2, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 2, 1,
        1, 2, 2, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 1, 2, 2, 1,
        1, 1, 2, 1, 1, 2, 1, 2, 1, 2, 0, 2, 1, 2, 1, 2, 1, 1, 2, 1, 1,
        1, 2, 2, 2, 3, 2, 1, 2, 2, 2, 2, 2, 2, 2, 1, 2, 3, 2, 2, 2, 1,
        1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1,
        1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

Character PacmanCharacter;
Character BlinkyCharacter;
Character ClydeCharacter;
Character InkyCharacter;
Character PinkyCharacter;

std::shared_ptr<GameEntity> Pacman = std::make_shared<GameEntity>("Pacman");
std::shared_ptr<GameEntity> Blinky = std::make_shared<GameEntity>("Blinky");
std::shared_ptr<GameEntity> Clyde = std::make_shared<GameEntity>("Clyde");
std::shared_ptr<GameEntity> Inky = std::make_shared<GameEntity>("Inky");
std::shared_ptr<GameEntity> Pinky = std::make_shared<GameEntity>("Pinky");

GameLogic::GameLogic()
{
    CellRows = CELL_ROWS;
    CellCols = CELL_COLS;
    CellSize = CELL_SIZE;

    Pacman->CellType = CellType::Pacman;

    SetStartingPositions();

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

    InitializeCharacter(Pacman, EnemyEntities, PacmanCharacter.Position.x, PacmanCharacter.Position.y, "./Assets/Pacman.png", 0.065f);
    InitializeCharacter(Blinky, EnemyEntities, BlinkyCharacter.Position.x, BlinkyCharacter.Position.y, "./Assets/Blinky.png");
    InitializeCharacter(Clyde, EnemyEntities, ClydeCharacter.Position.x, ClydeCharacter.Position.y, "./Assets/Clyde.png");
    InitializeCharacter(Inky, EnemyEntities, InkyCharacter.Position.x, InkyCharacter.Position.y, "./Assets/Inky.png");
    InitializeCharacter(Pinky, EnemyEntities, PinkyCharacter.Position.x, PinkyCharacter.Position.y, "./Assets/Pinky.png");

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
                }
                else
                {
                    Score++;
                }
                GameEntities.erase(GameEntities.begin() + i);
                PlaySound(CreditSound);
            }
        }
        GameEntities[i]->Render();
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
            BlinkyMove(DeltaTime);
            ClydeMove(DeltaTime);
            InkyMove(DeltaTime);
            PinkyMove(DeltaTime);
        }
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

void GameLogic::PacmanCollisionWithEnemy(const std::vector<std::shared_ptr<GameEntity>> &EnemyEntityVector)
{
    for (int i = 0; i < (int)EnemyEntityVector.size(); i++)
    {
        if (EnemyEntityVector[i]->CellType == CellType::Pacman)
            continue;
        Rectangle PacmanRec = {Pacman->GetPosition().x - Pacman->GetTexture().width * Pacman->GetScale() / 2, Pacman->GetPosition().y - Pacman->GetTexture().height * Pacman->GetScale() / 2, Pacman->GetTexture().width * Pacman->GetScale(), Pacman->GetTexture().height * Pacman->GetScale()};
        Rectangle EnemyRec = {EnemyEntityVector[i]->GetPosition().x - EnemyEntityVector[i]->GetTexture().width * EnemyEntityVector[i]->GetScale() / 2, EnemyEntityVector[i]->GetPosition().y - EnemyEntityVector[i]->GetTexture().height * EnemyEntityVector[i]->GetScale() / 2, EnemyEntityVector[i]->GetTexture().width * EnemyEntityVector[i]->GetScale(), EnemyEntityVector[i]->GetTexture().height * EnemyEntityVector[i]->GetScale()};
        if (CheckCollisionRecs(PacmanRec, EnemyRec))
        {
            Pacman->IsDead = true;
            PlaySound(PacmanDeadSound);
        }
    }
}

void GameLogic::PacmanMove(float DeltaTime)
{
    InitializeCharacterVelocity(PacmanCharacter, DeltaTime);
    CheckCollisionWithWalls(Pacman, PacmanCharacter);
    PacmanCollisionWithEnemy(EnemyEntities);

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

    if (Pacman->GetPosition().y - Pacman->GetTexture().height * Pacman->GetScale() / 2 >= 0 && PacmanDirection == Directions::Up)
    {
        Pacman->SetRotation(270.f);
        PacmanCharacter.Position.y -= PacmanCharacter.UpVelocity;
        Pacman->SetPosition(PacmanCharacter.Position.x, PacmanCharacter.Position.y);
    }
    if (Pacman->GetPosition().y + Pacman->GetTexture().height * Pacman->GetScale() / 2 <= GetScreenHeight() && PacmanDirection == Directions::Down)
    {
        Pacman->SetRotation(90.f);
        PacmanCharacter.Position.y += PacmanCharacter.DownVelocity;
        Pacman->SetPosition(PacmanCharacter.Position.x, PacmanCharacter.Position.y);
    }
    if (Pacman->GetPosition().x - Pacman->GetTexture().width * Pacman->GetScale() / 2 >= 0 && PacmanDirection == Directions::Left)
    {
        Pacman->SetRotation(180.f);
        PacmanCharacter.Position.x -= PacmanCharacter.LeftVelocity;
        Pacman->SetPosition(PacmanCharacter.Position.x, PacmanCharacter.Position.y);
    }
    if (Pacman->GetPosition().x + Pacman->GetTexture().width * Pacman->GetScale() / 2 <= GetScreenWidth() && PacmanDirection == Directions::Right)
    {
        Pacman->SetRotation(0.f);
        PacmanCharacter.Position.x += PacmanCharacter.RightVelocity;
        Pacman->SetPosition(PacmanCharacter.Position.x, PacmanCharacter.Position.y);
    }

    SecretDoor();
}

void GameLogic::SecretDoor()
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
    if (PacmanCharacter.Position.y <= Character.Position.y)
    {
        Character.Direction = Directions::Up;
    }
    if (PacmanCharacter.Position.y >= Character.Position.y)
    {
        Character.Direction = Directions::Down;
    }
    if (PacmanCharacter.Position.x >= Character.Position.x)
    {
        Character.Direction = Directions::Right;
    }
    if (PacmanCharacter.Position.x <= Character.Position.x)
    {
        Character.Direction = Directions::Left;
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
    PacmanCharacter.Speed = 100.f;
    BlinkyCharacter.Position = {220.f, 220.f};
    ClydeCharacter.Position = {400.f, 400.f};
    InkyCharacter.Position = {500.f, 500.f};
    PinkyCharacter.Position = {620.f, 620.f};
}

void GameLogic::InitializeCharacter(std::shared_ptr<GameEntity> &Entity, std::vector<std::shared_ptr<GameEntity>> &EntityVector, const float PosX, const float PosY, const char *FilePath, const float Scale)
{
    Entity->AddPositionComponent();
    Entity->AddVelocityComponent();
    Entity->AddSprite2DComponent(FilePath);
    Entity->SetPosition(PosX, PosY);
    Entity->SetRotation(0.f);
    Entity->SetScale(Scale);
    EntityVector.emplace_back(Entity);
    GameEntities.emplace_back(Entity);
}
