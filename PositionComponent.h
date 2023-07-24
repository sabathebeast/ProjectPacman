#pragma once
#include <Component.h>

class PositionComponent : public Component
{
public:
    virtual void SetPosition(float PositionX, float PositionY) override;

protected:
private:
    float m_PositionX = 0;
    float m_PositionY = 0;
};