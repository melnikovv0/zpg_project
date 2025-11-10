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

/*std::unique_ptr<Light> LightManager::extractLight(Light* lightPtr) {
    auto it = std::find_if(m_lights.begin(), m_lights.end(),
        [&](const std::unique_ptr<Light>& p) {
            return p.get() == lightPtr;
        }
    );

    if (it != m_lights.end()) {

        std::unique_ptr<Light> extractedPtr = std::move(*it);

        m_lights.erase(it);

        return extractedPtr;
    }

    return nullptr;
}*/