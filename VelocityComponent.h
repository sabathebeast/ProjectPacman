#pragma once
#include <Component.h>

class VelocityComponent : public Component
{
public:
    void SetVelocity(float VelocityX, float VelocityY) override;

protected:
private:
    float m_VelocityX{};
    float m_VelocityY{};
};