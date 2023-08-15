#include "GameEntity.h"
#include <VelocityComponent.h>
#include <PositionComponent.h>
#include <Sprite2DComponent.h>

void GameEntity::AddPositionComponent()
{
    ID = 1;
    std::shared_ptr<PositionComponent> positionComponent = std::make_shared<PositionComponent>();
    Components.emplace_back(positionComponent);
}

void GameEntity::AddVelocityComponent()
{
    ID = 2;
    std::shared_ptr<VelocityComponent> velocityComponent = std::make_shared<VelocityComponent>();
    Components.emplace_back(velocityComponent);
}

void GameEntity::AddSprite2DComponent(const char *filename)
{
    ID = 3;
    std::shared_ptr<Sprite2DComponent> sprite2DComponent = std::make_shared<Sprite2DComponent>(filename);
    Components.emplace_back(sprite2DComponent);

    m_texture = sprite2DComponent->GetTexture();
}

void GameEntity::AddSprite2DComponentWithTexture(Texture texture)
{
    ID = 4;
    std::shared_ptr<Sprite2DComponent> sprite2DComponent = std::make_shared<Sprite2DComponent>(texture);
    Components.emplace_back(sprite2DComponent);

    m_texture = sprite2DComponent->GetTexture();
}

void GameEntity::SetRotation(float rotation)
{
    m_rotation = rotation;
    for (int i = 0; i < (int)Components.size(); i++)
    {
        Components[i]->SetRotation(m_rotation);
    }
}

void GameEntity::SetPosition(float PositionX, float PositionY)
{
    m_positionX = PositionX;
    m_positionY = PositionY;
    for (int i = 0; i < (int)Components.size(); i++)
    {
        Components[i]->SetPosition(m_positionX, m_positionY);
    }
}

void GameEntity::SetVelocity(float VelocityX, float VelocityY)
{
    m_velocityX = VelocityX;
    m_velocityY = VelocityY;
    for (int i = 0; i < (int)Components.size(); i++)
    {
        Components[i]->SetVelocity(m_velocityX, m_velocityY);
    }
}

void GameEntity::Render()
{
    for (int i = 0; i < (int)Components.size(); i++)
    {
        if (!isCurrentlyDead)
        {
            Components[i]->Render({m_positionX, m_positionY}, m_rotation, m_width_scale, m_height_scale, m_color, m_frames, m_source_x);
        }
    }
}