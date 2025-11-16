#pragma once
#include <glm/mat4x4.hpp>
#include <memory>
#include <string>
#include <map>
#include "Texture.h"

class Model;
class ShaderProgram;
class Transformation;

class DrawableObject {
public:
    DrawableObject(Model* model, ShaderProgram* program)
        : model(model), program(program), m_texture(nullptr) {
    }

    void setModelMatrix(const glm::mat4& m) { baseMatrix = m; }

   
    void setTransform(const std::shared_ptr<Transformation>& t) { transform = t; }
    void setTexture(Texture* texture) { m_texture = texture; }

    void addUniform(const std::string& name, const glm::vec3& value);

    void update(float dt);
    void draw() const;

    ShaderProgram* getShaderProgram() const;

private:
    Model* model = nullptr;
    ShaderProgram* program = nullptr;

    glm::mat4 baseMatrix{ 1.0f };                          
    std::shared_ptr<Transformation> transform = nullptr; 

    Texture* m_texture;

    std::map<std::string, glm::vec3> m_uniformsVec3;
};
