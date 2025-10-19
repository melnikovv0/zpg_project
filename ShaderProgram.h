#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "Shader.h"

class ShaderProgram {
public:
    ShaderProgram(const std::string& vertexFilepath, const std::string& fragmentFilepath);
    ~ShaderProgram();

    void use() const;

    void setUniform(const char* name, float v) const;
    void setUniform(const char* name, const glm::mat4& m) const;
    void setUniform(const char* name, const glm::vec3& v) const;

private:
    GLuint programId = 0;
    void link(const Shader& vs, const Shader& fs);
};
