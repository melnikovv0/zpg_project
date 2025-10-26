#include "Light.h"
#include "LightManager.h"

Light::Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic)
    : position(position),
    ambient(ambient),
    diffuse(diffuse),
    specular(specular),
    constant(constant),
    linear(linear),
    quadratic(quadratic) {
}

void Light::setPosition(const glm::vec3& newPosition) {
    position = newPosition;

    if (m_manager) {
        m_manager->onLightUpdated();
    }
}

glm::vec3 Light::getPosition() const { return position; }
glm::vec3 Light::getAmbient() const { return ambient; }
glm::vec3 Light::getDiffuse() const { return diffuse; }
glm::vec3 Light::getSpecular() const { return specular; }
float Light::getConstant() const { return constant; }
float Light::getLinear() const { return linear; }
float Light::getQuadratic() const { return quadratic; }

void Light::setManager(LightManager* manager)
{
    m_manager = manager; 
}
