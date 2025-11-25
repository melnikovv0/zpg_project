#include "MatrixTransform.h"

// save transferred matrix
MatrixTransform::MatrixTransform(const glm::mat4& matrix)
    : m_matrix(matrix) {
}

// return matrix
glm::mat4 MatrixTransform::matrix() const {
    return m_matrix;
}