#pragma once
#include <vector>
#include <memory> 
#include <set>
#include "DrawableObject.h"
#include "Light.h" 
#include "Skybox.h"

class Model;
class ShaderProgram;

class Scene {
public:
    DrawableObject& add(Model* model, ShaderProgram* program);
    void update(float dt);
    void render() const;
    void clear();

    void setUpdateCallback(const std::function<void(float)>& callback);

    Light* addLight(std::unique_ptr<Light> light);
    const std::vector<std::unique_ptr<Light>>& getLights() const;

    std::set<ShaderProgram*> getUniqueShaders();

    void setSkybox(std::unique_ptr<Skybox> skybox);

    void drawSkybox(const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);


private:
    std::vector<DrawableObject> objects;

    std::vector<std::unique_ptr<Light>> m_lights;

    std::function<void(float)> m_UpdateCallback;

    std::unique_ptr<Skybox> m_Skybox;
};
