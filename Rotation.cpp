#include "Rotation.h"
#include <glm/gtc/matrix_transform.hpp>

glm::mat4 Rotation::matrix() const {
    glm::mat4 m(1.0f);
    glm::vec3 ax;

    if (glm::length(axis) > 0.0f) {
        ax = glm::normalize(axis);
    }
    else {
        ax = glm::vec3(0, 0, 1);
    }

    return glm::rotate(m, angle, ax);
}