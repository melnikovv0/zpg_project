#pragma once
#include "ISubject.h"
#include <glm/glm.hpp>

class LightManager;

class Light  {
public:
    Light(glm::vec3 position,
        glm::vec3 ambient,
        glm::vec3 diffuse,
        glm::vec3 specular,
        float constant = 1.0f,
        float linear = 0.09f,
        float quadratic = 0.032f);

    void setPosition(const glm::vec3& newPosition);
    glm::vec3 getPosition() const;

    glm::vec3 getAmbient() const;
    glm::vec3 getDiffuse() const;
    glm::vec3 getSpecular() const;
    float getConstant() const;
    float getLinear() const;
    float getQuadratic() const;

    void setManager(LightManager* manager);

private:
    glm::vec3 position;

    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;

    LightManager* m_manager = nullptr;
};