#include "ShaderProgram.h"
#include <iostream>
using namespace std;

ShaderProgram::ShaderProgram(const char* vertexSrc, const char* fragmentSrc) : id(0) {
    Shader vs(vertexSrc, GL_VERTEX_SHADER);
    Shader fs(fragmentSrc, GL_FRAGMENT_SHADER);
    link(vs, fs);
}

ShaderProgram::~ShaderProgram() {
    if (id != 0) {
        glDeleteProgram(id);
    }
}

void ShaderProgram::use() const {
    glUseProgram(id);
}

void ShaderProgram::link(const Shader& vs, const Shader& fs) {
    id = glCreateProgram();
    glAttachShader(id, vs.id);
    glAttachShader(id, fs.id);
    glLinkProgram(id);

    GLint success;
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        char log[512];
        glGetProgramInfoLog(id, 512, nullptr, log);
        std::cerr << "ERROR: Shader program linking failed\n" << log << std::endl;
    }
}
