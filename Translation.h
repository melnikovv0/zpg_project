// Translation.h
#pragma once
#include "Transformation.h"
#include <glm/vec3.hpp>

class Translation : public Transformation {
public:
    Translation() : t(0.0f) {}
    explicit Translation(const glm::vec3& v) : t(v) {}

    void set(const glm::vec3& v) { t = v; }
    glm::vec3 value() const { return t; }

    glm::mat4 matrix() const override;

private:
    glm::vec3 t; // смещение
};
