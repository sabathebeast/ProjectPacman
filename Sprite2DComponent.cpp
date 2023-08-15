#include "Sprite2DComponent.h"

Sprite2DComponent::Sprite2DComponent(const char *filepath)
{
    m_texture = LoadTexture(filepath);
}

Sprite2DComponent::Sprite2DComponent(Texture texture)
{
    m_texture = texture;
}

Sprite2DComponent::~Sprite2DComponent()
{
    // UnloadTexture(m_texture);
}

void Sprite2DComponent::Render(Vector2 position, float rotation, float WidthScale, float HeightScale, Color color, int frames, float SourceX)
{
    DrawTexturePro(m_texture, Rectangle{SourceX, 0.f, (float)m_texture.width / frames, (float)m_texture.height}, Rectangle{position.x, position.y, (float)m_texture.width * WidthScale, (float)m_texture.height * HeightScale}, Vector2{m_texture.width * WidthScale / 2.f, m_texture.height * HeightScale / 2.f}, rotation, color);
}
