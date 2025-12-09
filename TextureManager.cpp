#include "TextureManager.h"
#include <stdexcept>
#include <iostream>
#include <vector>
#include "stb_image.h"

void TextureManager::loadTextures() {

    try {
        m_Textures["fence_tex"] = std::make_unique<Texture>("assets/wooden_fence.png");
        m_Textures["grass_tex"] = std::make_unique<Texture>("assets/grass.png"); 
        m_Textures["shrek_tex"] = std::make_unique<Texture>("assets/shrek.png");
        m_Textures["fiona_tex"] = std::make_unique<Texture>("assets/fiona.png");
        m_Textures["toiled_tex"] = std::make_unique<Texture>("assets/toiled.jpg");
        m_Textures["sun_tex"] = std::make_unique<Texture>("assets/sun.jpg");
        m_Textures["earth_tex"] = std::make_unique<Texture>("assets/earth.jpg");
        m_Textures["moon_tex"] = std::make_unique<Texture>("assets/moon.jpg");

        std::vector<std::string> faces = {
            "assets/posx.jpg", "assets/negx.jpg",
            "assets/posy.jpg", "assets/negy.jpg",
            "assets/posz.jpg", "assets/negz.jpg"
        };
        m_Textures["skybox"] = std::make_unique<Texture>(faces);

    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }
}

Texture* TextureManager::getTexture(const std::string& name) {
    auto it = m_Textures.find(name);
    if (it != m_Textures.end()) {
        return it->second.get();
    }
    return nullptr;
}

