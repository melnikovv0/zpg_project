#pragma once
#include "Transformation.h"
#include <glm/mat4x4.hpp>


class MatrixTransform : public Transformation {
public:
    // accept finished matrix
    explicit MatrixTransform(const glm::mat4& matrix);

    glm::mat4 matrix() const override;

private:
    glm::mat4 m_matrix;
};