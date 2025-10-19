#pragma once
#include <GL/glew.h>
#include <string>

class Shader {
public:
    Shader(const std::string& filepath, GLenum shaderType);
    ~Shader();

    GLuint getShaderId() const;

private:
    GLuint shaderId = 0;     

    friend class ShaderProgram;
};
