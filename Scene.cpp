// Scene.cpp
#include "Scene.h"

DrawableObject& Scene::add(Model* model, ShaderProgram* program) { // predat novy object
    objects.emplace_back(model, program); // vytvr novy DO hned na konci seznamu, předáním modelu a programu do konstruktoru.“
    return objects.back(); //Po přidání objektu metoda vrátí odkaz (&) na něj,umožňuje s ním ihned po vytvoření objektu něco udělat
}

void Scene::update(float dt) {
    // Сначала вызываем update у всех объектов, как и раньше
    for (auto& o : objects) {
        o.update(dt);
    }

    // --- ДОБАВЛЕНО: Вызываем наш специальный колбэк для этой сцены ---
    if (m_UpdateCallback) {
        m_UpdateCallback(dt);
    }
}

void Scene::render() const { // nakresli všechny
    for (const auto& o : objects) o.draw();
}



void Scene::clear() { objects.clear(); }

void Scene::setUpdateCallback(const std::function<void(float)>& callback) {
    m_UpdateCallback = callback;
}
