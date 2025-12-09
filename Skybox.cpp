#include "Skybox.h"
#include "Model.h"
#include "ShaderProgram.h"

Skybox::Skybox(Model* model, ShaderProgram* shader, GLuint textureID)
    : m_model(model), m_shader(shader), m_textureID(textureID)
{
}

void Skybox::draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix) {
    if (!m_model || !m_shader) return;

    glDepthFunc(GL_LEQUAL);

    m_shader->use();

    m_shader->setUniform("view", viewMatrix);
    m_shader->setUniform("projection", projectionMatrix);
    m_shader->setUniform("skybox", 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureID);

    m_model->draw();

    glDepthFunc(GL_LESS);
}