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
    PowerUp,
    MAX
};

enum class State : unsigned char
{
    Nothing,
    PowerUp,
    Scatter,
    Chase,
    Frightened
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
    void Render();
    inline const Texture GetTexture() const { return m_texture; }
    inline const Vector2 GetPosition() const { return {m_positionX, m_positionY}; }
    inline void SetTextureColor(Color color) { m_color = color; }
    inline const std::string GetName() const { return m_name; }
    inline const float GetWidthScale() const { return m_width_scale; }
    inline const float GetHeightScale() const { return m_height_scale; }
    inline void SetWidthScale(float WidthScale) { m_width_scale = WidthScale; }
    inline void SetHeightScale(float HeightScale) { m_height_scale = HeightScale; }
    inline const int GetTextureFrames() const { return m_frames; }
    inline void SetTextureFrames(float Frames) { m_frames = Frames; }
    inline const float GetTextureSourceX() const { return m_source_x; }
    inline void SetTextureSourceX(float SourceX) { m_source_x = SourceX; }
    inline const float GetRotation() const { return m_rotation; }
    bool IsDead = false;
    bool isCurrentlyDead = false;
    CellType CellType;
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
    float m_width_scale = 1.f;
    float m_height_scale = 1.f;
    int m_frames = 1;
    float m_source_x = 0.f;
    Texture m_texture;
    Color m_color = WHITE;
    std::string m_name;
};