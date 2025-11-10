#pragma once

#include <glm/glm.hpp>

class LightManager;

class Light {
public:
    enum class LightType {
        Directional, 
        Point,       
        Spotlight    
    };

    // Point
    Light(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);

    // Directional
    Light(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, bool dummy);

    // Spotlight
    Light(glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);


    void setPosition(const glm::vec3& position);
    void setDirection(const glm::vec3& direction);
    void setColors(const glm::vec3& ambient, const glm::vec3& diffuse, const glm::vec3& specular);
    void setManager(LightManager* manager);

    void setAttenuation(float constant, float linear, float quadratic);


    LightType getType() const { return m_type; }
    glm::vec3 getPosition() const { return m_position; }
    glm::vec3 getDirection() const { return m_direction; }
    glm::vec3 getAmbient() const { return m_ambient; }
    glm::vec3 getDiffuse() const { return m_diffuse; }
    glm::vec3 getSpecular() const { return m_specular; }
    float getConstant() const { return m_constant; }
    float getLinear() const { return m_linear; }
    float getQuadratic() const { return m_quadratic; }
    float getCutOff() const { return m_cutOff; }
    float getOuterCutOff() const { return m_outerCutOff; }


private:
    LightManager* m_manager = nullptr;
    LightType m_type;

    glm::vec3 m_position;
    glm::vec3 m_direction;

    glm::vec3 m_ambient;
    glm::vec3 m_diffuse;
    glm::vec3 m_specular;

    float m_constant = 1.0f;
    float m_linear = 0.09f;
    float m_quadratic = 0.032f;

    // Spotlight
    float m_cutOff; //  Jedná se o vnitřní kužel  osvětleno plnou jasností 100 %
    float m_outerCutOff;// Jedná se o vnější kužel. Vše, co se nachází mimo tento úhel, je zcela ve tmě 0 % jasu
};