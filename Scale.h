#pragma once
#include "Transformation.h"
#include <glm/vec3.hpp>

class Scale : public Transformation {
public:
    Scale() : s(1.0f) {}
    explicit Scale(const glm::vec3& v) : s(v) {}

    void set(const glm::vec3& v) { s = v; }
    glm::vec3 value() const { return s; }

    glm::mat4 matrix() const override;

private:
    glm::vec3 s; // „paměť“ objektu
};
