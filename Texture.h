#pragma once
#include <GL/glew.h>
#include <string>

class Texture {
public:
    Texture(const std::string& filepath);
    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    void bind(GLuint textureUnit = 0) const;

private:
    GLuint m_textureID = 0;
};