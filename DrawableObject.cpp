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

    glm::mat4 M = baseMatrix;
    if (transform) M = M * transform->matrix();

    program->use();

    program->setUniform("modelMatrix", M);

    for (const auto& pair : m_uniformsVec3) {
        program->setUniform(pair.first.c_str(), pair.second);
    }
    model->draw(); 

    glUseProgram(0);
}

ShaderProgram* DrawableObject::getShaderProgram() const
{
    return program;
}
