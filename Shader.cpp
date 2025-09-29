#include "Shader.h"
#include <iostream>
using namespace std;

Shader::Shader(const char* source, GLenum type) : id(0) {
    compile(source, type);
}

Shader::~Shader() {
    if (id != 0) {
        glDeleteShader(id);
    }
}

void Shader::compile(const char* source, GLenum type) {
    id = glCreateShader(type);
    glShaderSource(id, 1, &source, nullptr);
    glCompileShader(id);

    GLint success;
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        char log[512];
        glGetShaderInfoLog(id, 512, nullptr, log);
        std::cerr << "ERROR: Shader compilation failed\n" << log << std::endl;
    }
}
