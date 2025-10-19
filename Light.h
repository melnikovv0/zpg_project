#pragma once

#include <glm/glm.hpp>

class Light {
public:
    // Параметры света
    glm::vec3 Position;
    glm::vec3 Color;

    // Конструктор
    explicit Light(glm::vec3 position = glm::vec3(0.0f), glm::vec3 color = glm::vec3(1.0f))
        : Position(position), Color(color) {
    }
};