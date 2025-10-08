#pragma once
#include <GL/glew.h>

class Shader {
public:
    Shader(const char* source, GLenum type);
    ~Shader();

private:
    GLuint shaderId = 0;         // id объекта шейдера в GPU
    void compile(const char* source, GLenum type);

    friend class ShaderProgram;
};
