#pragma once
#include "Transformation.h"
#include <glm/vec3.hpp>

class Rotation : public Transformation {
public:
    Rotation() : angle(0.0f), axis(0, 0, 1) {}
    Rotation(float angleRad, const glm::vec3& ax) : angle(angleRad), axis(ax) {}

    void setAngle(float angleRad) { angle = angleRad; }
    void setAxis(const glm::vec3& ax) { axis = ax; }

    float getAngle() const { return angle; }
    glm::vec3 getAxis() const { return axis; }

    glm::mat4 matrix() const override;

private:
    float angle;     
    glm::vec3 axis;  
};
