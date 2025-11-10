#include "Light.h"
#include "LightManager.h"

// Point light
Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : m_type(LightType::Point), m_position(position), m_direction({ 0,0,0 }),// Direction not used
    m_ambient(ambient), m_diffuse(diffuse), m_specular(specular),
    m_cutOff(0), m_outerCutOff(0)  // Angles are not used
{
}

// Directional (smerove svetlo)
Light::Light(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, bool dummy)
    : m_type(LightType::Directional), m_position({ 0,0,0 }), m_direction(direction), // Position not used
    m_ambient(ambient), m_diffuse(diffuse), m_specular(specular),
    m_cutOff(0), m_outerCutOff(0) 
{

    m_constant = 1.0f;
    m_linear = 0.0f;
    m_quadratic = 0.0f;
}

// Spotlight (Reflektor)
Light::Light(glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
    : m_type(LightType::Spotlight), m_position(position), m_direction(direction),
    m_ambient(ambient), m_diffuse(diffuse), m_specular(specular),
    m_cutOff(cutOff), m_outerCutOff(outerCutOff)
{
}

void Light::setPosition(const glm::vec3& position) {
    m_position = position;
    if (m_manager) m_manager->onLightUpdated();
}

void Light::setDirection(const glm::vec3& direction) {
    m_direction = direction;
    if (m_manager) m_manager->onLightUpdated();
}

void Light::setColors(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular) {
    m_ambient = ambient;
    m_diffuse = diffuse;
    m_specular = specular;
    if (m_manager) m_manager->onLightUpdated();
}

void Light::setManager(LightManager* manager) {
    m_manager = manager;
}

void Light::setAttenuation(float constant, float linear, float quadratic) { 
    m_constant = constant; // jestli 0 nekonečně jasné.
    m_linear = linear; // Způsobuje, že světlo rovnoměrně slábne s vzdáleností.
    m_quadratic = quadratic; // Způsobuje, že světlo slábne velmi rychle
}
