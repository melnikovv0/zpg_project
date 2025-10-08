#pragma once
#include <glm/mat4x4.hpp>

// Базовый интерфейс трансформации (проектivní prostor, 4×4)
class Transformation {
public:
    virtual ~Transformation() = default;

    // Вернуть матрицу трансформации 4×4 (model space)
    virtual glm::mat4 matrix() const = 0;

    // Для анимаций — обновить внутреннее состояние с учётом прошедшего времени (сек)
    virtual void update(float /*dt*/) {}
};
