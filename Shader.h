#pragma once
#include <GL/glew.h>
#include <string>

class Shader {
public:
    Shader(const std::string& filepath, GLenum shaderType);
    ~Shader();

    // Геттер для ID
    GLuint getShaderId() const;

private:
    GLuint shaderId = 0;         // id объекта шейдера в GPU

    friend class ShaderProgram;
};
