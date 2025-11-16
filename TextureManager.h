#pragma once
#include <map>
#include <memory>
#include <string>
#include "Texture.h"

class TextureManager {
public:
    void loadTextures();
    Texture* getTexture(const std::string& name);

private:
    std::map<std::string, std::unique_ptr<Texture>> m_Textures;
};