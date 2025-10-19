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

    //statická poloha
    void setModelMatrix(const glm::mat4& m) { baseMatrix = m; }

   
    void setTransform(const std::shared_ptr<Transformation>& t) { transform = t; }

    void addUniform(const std::string& name, const glm::vec3& value);

    void update(float dt);
    void draw() const;

private:
    Model* model = nullptr;
    ShaderProgram* program = nullptr;

<<<<<<< HEAD
    glm::mat4 baseMatrix{ 1.0f };                          
    std::shared_ptr<Transformation> transform = nullptr; 
=======
    glm::mat4 baseMatrix{ 1.0f };                          // то, что ты раньше задавал setModelMatrix()
    std::shared_ptr<Transformation> transform = nullptr; // дерево трансформаций

    std::map<std::string, glm::vec3> m_uniformsVec3;
>>>>>>> develop
};
