#include "DynamicRotation.h"

DynamicRotation::DynamicRotation(float speed, const glm::vec3& axis)
    : Rotation(0.0f, axis), m_speed(speed)
{
}

void DynamicRotation::update(float dt) {
    float newAngle = getAngle() + m_speed * dt;

    if (newAngle > 360.0f) newAngle -= 360.0f;

    setAngle(newAngle);
}