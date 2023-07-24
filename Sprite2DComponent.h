#pragma once
#include <Component.h>
#include <raylib.h>

class Sprite2DComponent : public Component
{
public:
    Sprite2DComponent(const char *filepath);
    Sprite2DComponent(Texture texture);
    ~Sprite2DComponent();
    void Render(Vector2 position, float rotation, float scale) override;
    inline Texture GetTexture() const { return m_texture; }

protected:
private:
    Texture m_texture;
};