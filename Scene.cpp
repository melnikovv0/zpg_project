// Scene.cpp
#include "Scene.h"

DrawableObject& Scene::add(Model* model, ShaderProgram* program) {
    objects.emplace_back(model, program);
    return objects.back();
}

void Scene::update(float dt) {
    for (auto& o : objects) o.update(dt);
}

void Scene::render() const {
    for (const auto& o : objects) o.draw();
}

void Scene::clear() { objects.clear(); }
