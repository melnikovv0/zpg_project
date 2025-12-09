#pragma once
#include <GL/glew.h>
#include <string>
#include <vector>

class Texture {
public:
    Texture(const std::string& filepath);

    Texture(const std::vector<std::string>& faces);

    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    void bind(GLuint textureUnit = 0) const;

    GLuint getID() const { return m_textureID; }

private:
    GLuint m_textureID = 0;
    GLenum m_type = GL_TEXTURE_2D;
};