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
    UnloadTexture(m_texture);
}

void Sprite2DComponent::Render(Vector2 position, float rotation, float scale)
{
    // DrawTextureEx(m_texture, position, rotation, scale, WHITE);

    DrawTexturePro(m_texture, Rectangle{0, 0, (float)m_texture.width, (float)m_texture.height}, Rectangle{position.x, position.y, (float)m_texture.width * scale, (float)m_texture.height * scale}, Vector2{m_texture.width * scale / 2.f, m_texture.height * scale / 2.f}, rotation, Color{WHITE});
}
