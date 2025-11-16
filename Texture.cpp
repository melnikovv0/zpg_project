#include "Texture.h"
#include <stdexcept>
#include <iostream>

// "Активируем" библиотеку stb_image.h
#pragma warning(push)
#pragma warning(disable: 26495)
#pragma warning(disable: 26451)
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#pragma warning(pop)

Texture::Texture(const std::string& filepath) {
    int text_width, text_height, channels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filepath.c_str(), &text_width, &text_height, &channels, 0);
    if (!data) {
        throw std::runtime_error("Failed to load texture: " + filepath);
    }

    GLenum format = GL_RGB;
    if (channels == 4) {
        format = GL_RGBA;
    }

    // Код из твоего примера:
    glGenTextures(1, &m_textureID);
    glActiveTexture(GL_TEXTURE0); // Активируем юнит 0 (можно и позже)
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    glTexImage2D(GL_TEXTURE_2D, 0, format, text_width, text_height, 0, format, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Освобождаем память CPU, данные уже на GPU
    stbi_image_free(data);
    std::cout << "Loaded texture: " << filepath << std::endl;
}

Texture::~Texture() {
    glDeleteTextures(1, &m_textureID);
}

void Texture::bind(GLuint textureUnit) const {
    glActiveTexture(GL_TEXTURE0 + textureUnit);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
}