#pragma once
#include <vector>
#include <Component.h>
#include <memory>
#include <raylib.h>
#include <string>

enum class CellType : unsigned char
{
    Empty,
    Wall,
    Food,
    Enemy,
    Pacman,
    MAX

};

enum class EntityType : unsigned char
{
    Nothing,
    Pacman,
    Enemy,
    Food,
    PowerUp
};

enum class State : unsigned char
{
    Nothing,
    PowerUp
};

enum class Enemy : unsigned char
{
    Blinky,
    Clyde,
    Inky,
    Pinky
};

class GameEntity
{
public:
    GameEntity(std::string name)
        : m_name(name)
    {
    }
    ~GameEntity(){};
    void AddVelocityComponent();
    void AddPositionComponent();
    void AddSprite2DComponent(const char *filename);
    void AddSprite2DComponentWithTexture(Texture texture);
    void SetPosition(float PositionX, float PositionY);
    void SetVelocity(float VelocityX, float VelocityY);
    void SetRotation(float rotation);
    void SetScale(float scale);
    void Render();
    inline const float GetScale() const { return m_scale; }
    inline const Texture GetTexture() const { return m_texture; }
    inline const Vector2 GetPosition() const { return {m_positionX, m_positionY}; }
    inline Color SetTextureColor(Color color)
    {
        m_color = color;
        return color;
    }
    inline const std::string GetName() const { return m_name; }
    bool IsDead = false;
    CellType CellType;
    EntityType EntityType;
    State State;
    Enemy EnemyType;

protected:
private:
    unsigned char ID = 0;
    std::vector<std::shared_ptr<Component>> Components;
    float m_positionX = 0.f;
    float m_positionY = 0.f;
    float m_velocityX = 0.f;
    float m_velocityY = 0.f;
    float m_rotation = 0.f;
    float m_scale = 1.f;
    Texture m_texture;
    Color m_color = WHITE;
    std::string m_name;
};