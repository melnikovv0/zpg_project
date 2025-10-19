#include "DrawableObject.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

void DrawableObject::addUniform(const std::string& name, const glm::vec3& value) {
    m_uniformsVec3[name] = value;
}

void DrawableObject::update(float dt) {
    if (transform) transform->update(dt);
}

void DrawableObject::draw() const {
    if (!program || !model) return;

    // Вычисляем итоговую model-матрицу
    glm::mat4 M = baseMatrix;
    if (transform) M = M * transform->matrix();

    // 1. Активируем шейдер
    program->use();

    // 2. Отправляем обязательную modelMatrix
    program->setUniform("modelMatrix", M);

    // --- ДОБАВЛЕНО: Отправляем все дополнительные uniform'ы ---
    // Проходим в цикле по всем сохраненным uniform-переменным (например, "objectColor")
    for (const auto& pair : m_uniformsVec3) {
        // И отправляем каждую из них в шейдер
        program->setUniform(pair.first.c_str(), pair.second);
    }
    // ----------------------------------------------------

    // 3. Рисуем модель
    model->draw();
}