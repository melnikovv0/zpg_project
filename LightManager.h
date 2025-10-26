#pragma once
#include <vector>
#include <memory> 
#include "Light.h"
#include "ISubject.h" 

class LightManager : public ISubject {
public:
    LightManager();
    ~LightManager();

 
    Light* addLight(std::unique_ptr<Light> light);

    void onLightUpdated();
    void clear();

    const std::vector<std::unique_ptr<Light>>& getLights() const;

private:
    std::vector<std::unique_ptr<Light>> m_lights;
};