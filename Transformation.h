#pragma once
#include <glm/mat4x4.hpp>

class Transformation {
public:
    virtual ~Transformation() = default;

    virtual glm::mat4 matrix() const = 0;

    virtual void update(float /*dt*/) {}
};
