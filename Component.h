#pragma once
#include <raylib.h>

class Component
{
public:
    virtual ~Component() {}
    virtual void SetPosition(float PositionX, float PositionY){};
    virtual void SetVelocity(float VelocityX, float VelocityY){};
    virtual void Render(Vector2 position, float rotation, float WidthScale, float HeightScale, Color color, int frames, float SourceX){};
    virtual void SetRotation(float rotation){};
};