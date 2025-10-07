#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

class Shader {
public:
    Shader(const char* source, GLenum type);
    ~Shader();

private:
    GLuint id;
    void compile(const char* source, GLenum type);

    friend class ShaderProgram;
};

#endif
