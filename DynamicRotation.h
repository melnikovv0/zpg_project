#pragma once
#include "Rotation.h"

class DynamicRotation : public Rotation {
public:
    // speed 
    DynamicRotation(float speed, const glm::vec3& axis);

    void update(float dt) override;

private:
    float m_speed;
};