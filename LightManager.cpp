#include "LightManager.h"

LightManager::LightManager() {}
LightManager::~LightManager() {}

Light* LightManager::addLight(std::unique_ptr<Light> light) {

    light->setManager(this);
    m_lights.push_back(std::move(light));
    return m_lights.back().get();
}

void LightManager::onLightUpdated() {
    notifyObservers();
}

void LightManager::clear() {
    m_lights.clear();
}

const std::vector<std::unique_ptr<Light>>& LightManager::getLights() const {
    return m_lights;
}