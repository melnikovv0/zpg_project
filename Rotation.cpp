// Rotation.cpp
#include "Rotation.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Rotation::matrix() const {
    glm::mat4 m(1.0f);
    float len = glm::length(axis);
    glm::vec3 ax = (len > 0.0f) ? axis / len : glm::vec3(0, 0, 1);
    return glm::rotate(m, angle, ax);
}