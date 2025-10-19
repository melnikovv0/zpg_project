#include "ShaderProgram.h"
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
