#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

class Model;
class ShaderProgram;

class Skybox {
public:
    Skybox(Model* model, ShaderProgram* shader, GLuint textureID);

    void draw(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

private:
    Model* m_model;
    ShaderProgram* m_shader;
    GLuint m_textureID;
};