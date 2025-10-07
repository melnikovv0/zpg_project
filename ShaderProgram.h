#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#include "Shader.h"

class ShaderProgram {
public:
    ShaderProgram(const char* vertexSrc, const char* fragmentSrc);
    ~ShaderProgram();

    void use() const;

private:
    GLuint id;
    void link(const Shader& vs, const Shader& fs);
};

#endif
