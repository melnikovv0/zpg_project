#include "DrawableObject.h"
#include "Model.h"
#include "ShaderProgram.h"
#include "Transformation.h"

void DrawableObject::update(float dt) {
    if (transform) transform->update(dt);
}

void DrawableObject::draw() const {
    if (!program || !model) return;

    // Итоговая матрица: базовая * (собранные трансформации)
    glm::mat4 M = baseMatrix;
    if (transform) M = M * transform->matrix();

    program->use();
    program->setUniform("modelMatrix", M);
    model->draw();
}
