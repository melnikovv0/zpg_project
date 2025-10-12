#pragma once
#include <glm/mat4x4.hpp>
#include <memory>

class Model;
class ShaderProgram;
class Transformation;

class DrawableObject {
public:
    DrawableObject(Model* model, ShaderProgram* program)
        : model(model), program(program) {
    }

    //statická poloha
    void setModelMatrix(const glm::mat4& m) { baseMatrix = m; }

   
    void setTransform(const std::shared_ptr<Transformation>& t) { transform = t; }

    void update(float dt);
    void draw() const;

private:
    Model* model = nullptr;
    ShaderProgram* program = nullptr;

    glm::mat4 baseMatrix{ 1.0f };                          
    std::shared_ptr<Transformation> transform = nullptr; 
};
