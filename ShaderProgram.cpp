#include "ShaderProgram.h"
#include "Camera.h"
#include "LightManager.h" 
#include <iostream>
#include <glm/gtc/type_ptr.hpp>

ShaderProgram::ShaderProgram(const std::string& vertexFilepath, const std::string& fragmentFilepath) {
    Shader vs(vertexFilepath, GL_VERTEX_SHADER);
    Shader fs(fragmentFilepath, GL_FRAGMENT_SHADER);
    link(vs, fs);
}

ShaderProgram::~ShaderProgram() {
    if (programId != 0) {
        glDeleteProgram(programId);
    }
}

void ShaderProgram::use() const {
    glUseProgram(programId);


}


void ShaderProgram::update(ISubject* subject) {
    if (!subject) return;

    this->use(); 


    if (Camera* camera = dynamic_cast<Camera*>(subject)) {
        this->setUniform("viewMatrix", camera->getViewMatrix());
        this->setUniform("viewPos", camera->Position);
    }
    else if (LightManager* lightManager = dynamic_cast<LightManager*>(subject)) {
        const auto& lights = lightManager->getLights();
        this->setUniform("numberOfLights", (int)lights.size());

        for (int i = 0; i < lights.size(); ++i) {
            std::string baseName = "lights[" + std::to_string(i) + "]";
            this->setUniform((baseName + ".position").c_str(), lights[i]->getPosition());
            this->setUniform((baseName + ".ambient").c_str(), lights[i]->getAmbient());
            this->setUniform((baseName + ".diffuse").c_str(), lights[i]->getDiffuse());
            this->setUniform((baseName + ".specular").c_str(), lights[i]->getSpecular());
            this->setUniform((baseName + ".constant").c_str(), lights[i]->getConstant());
            this->setUniform((baseName + ".linear").c_str(), lights[i]->getLinear());
            this->setUniform((baseName + ".quadratic").c_str(), lights[i]->getQuadratic());
        }
    }
}
void ShaderProgram::setUniform(const char* name, int v) const {
    GLint loc = glGetUniformLocation(programId, name);
    if (loc != -1) glUniform1i(loc, v);
}

void ShaderProgram::setUniform(const char* name, float v) const {
    GLint loc = glGetUniformLocation(programId, name);
    if (loc != -1) glUniform1f(loc, v);
}

void ShaderProgram::setUniform(const char* name, const glm::mat4& m) const {
    GLint loc = glGetUniformLocation(programId, name);
    if (loc != -1) glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m));
}

void ShaderProgram::setUniform(const char* name, const glm::vec3& v) const {
    GLint loc = glGetUniformLocation(programId, name);
    if (loc != -1) {
        glUniform3fv(loc, 1, glm::value_ptr(v));
    }
}

void ShaderProgram::link(const Shader& vs, const Shader& fs) {
    programId = glCreateProgram();
    glAttachShader(programId, vs.shaderId);
    glAttachShader(programId, fs.shaderId);
    glLinkProgram(programId);

    GLint success = GL_FALSE;
    glGetProgramiv(programId, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(programId, 512, nullptr, log);
        std::cerr << "ERROR: Shader program linking failed\n" << log << std::endl;
    }
}
