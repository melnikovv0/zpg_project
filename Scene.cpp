#include "Scene.h"

DrawableObject& Scene::add(Model* model, ShaderProgram* program) { 
    objects.emplace_back(model, program); 
    return objects.back(); 
}

void Scene::update(float dt) {
    for (auto& o : objects) {
        o.update(dt);
    }

    if (m_UpdateCallback) {
        m_UpdateCallback(dt);
    }
}

void Scene::render() const { 
    for (const auto& o : objects) o.draw();
}



void Scene::clear() { objects.clear(); }

void Scene::setUpdateCallback(const std::function<void(float)>& callback) {
    m_UpdateCallback = callback;
}

Light* Scene::addLight(std::unique_ptr<Light> light) {
    m_lights.push_back(std::move(light));
    return m_lights.back().get();
}

const std::vector<std::unique_ptr<Light>>& Scene::getLights() const {
    return m_lights;
}

std::set<ShaderProgram*> Scene::getUniqueShaders() {
    std::set<ShaderProgram*> shaders;
    for (const auto& obj : objects) {
        shaders.insert(obj.getShaderProgram());
    }
    return shaders;
}
