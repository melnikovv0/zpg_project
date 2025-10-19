#include "Shader.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

Shader::Shader(const std::string& filepath, GLenum shaderType) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("ERROR: Unable to open shader file: " + filepath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); 
    std::string shaderCode = buffer.str();
    const char* src = shaderCode.c_str();

    shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &src, nullptr);
    glCompileShader(shaderId);

    GLint success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        throw std::runtime_error("ERROR: Shader compilation failed for " + filepath + "\n" + infoLog);
    }
}

Shader::~Shader() {
    if (shaderId != 0) {
        glDeleteShader(shaderId);
    }
}

GLuint Shader::getShaderId() const {
    return shaderId;
}