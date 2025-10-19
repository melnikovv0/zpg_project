#pragma once
#include <glm/mat4x4.hpp>
#include <memory>
#include <string>
#include <map>

class Model;
class ShaderProgram;
class Transformation;

class DrawableObject {
public:
    DrawableObject(Model* model, ShaderProgram* program)
        : model(model), program(program) {
    }

    void setModelMatrix(const glm::mat4& m) { baseMatrix = m; }

   
    void setTransform(const std::shared_ptr<Transformation>& t) { transform = t; }

    void addUniform(const std::string& name, const glm::vec3& value);

    void update(float dt);
    void draw() const;

private:
    Model* model = nullptr;
    ShaderProgram* program = nullptr;

    glm::mat4 baseMatrix{ 1.0f };                          
    std::shared_ptr<Transformation> transform = nullptr; 

    std::map<std::string, glm::vec3> m_uniformsVec3;
};
