#pragma once
#include <vector>
#include <Component.h>
#include <memory>
#include <raylib.h>

enum class ComponentType : unsigned char
{
    CT_PositionComponent = 1,
    CT_VelocityComponent,
    CT_Sprite2DComponent,

    CT_Max
};

class GameEntity
{
public:
    GameEntity();
    ~GameEntity();
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
    bool BlockPacman{false};

protected:
private:
    unsigned char ID{};
    std::vector<std::shared_ptr<Component>> Components{};
    float m_positionX{};
    float m_positionY{};
    float m_velocityX{};
    float m_velocityY{};
    float m_rotation{};
    float m_scale{1};
    Texture m_texture{};
};