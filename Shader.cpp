#include "Shader.h"
#include <iostream>

Shader::Shader(const char* source, GLenum type) {
    compile(source, type);
}

Shader::~Shader() {
    if (shaderId != 0) {
        glDeleteShader(shaderId);
    }
}

void Shader::compile(const char* source, GLenum type) {
    shaderId = glCreateShader(type);
    glShaderSource(shaderId, 1, &source, nullptr);
    glCompileShader(shaderId);

    GLint success = GL_FALSE;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(shaderId, 512, nullptr, log);
        std::cerr << "ERROR: Shader compilation failed\n" << log << std::endl;
    }
}
