#include "ShaderManager.h"
#include <string> 

void ShaderManager::loadShaders() {

    std::string shader_path = "";

    m_Shaders["green"] = std::make_unique<ShaderProgram>(shader_path + "simple.vert", shader_path + "green.frag");

    m_Shaders["normal_color"] = std::make_unique<ShaderProgram>(shader_path + "normal_color.vert", shader_path + "normal_color.frag");

    std::string vs_lighting_path = shader_path + "phong.vert";
    m_Shaders["constant"] = std::make_unique<ShaderProgram>(vs_lighting_path, shader_path + "constant.frag");
    m_Shaders["lambert"] = std::make_unique<ShaderProgram>(vs_lighting_path, shader_path + "lambert.frag");

    m_Shaders["phong"] = std::make_unique<ShaderProgram>(vs_lighting_path, shader_path + "phong.frag");
    m_Shaders["blinn"] = std::make_unique<ShaderProgram>(vs_lighting_path, shader_path + "blinn.frag");

}


ShaderProgram* ShaderManager::getShader(const std::string& name) {
    auto it = m_Shaders.find(name);

    if (it != m_Shaders.end()) {
        return it->second.get();
    }

    throw std::runtime_error("ShaderManager Error: Shader program not found: " + name);
}

const std::map<std::string, std::unique_ptr<ShaderProgram>>& ShaderManager::getAllShaders() const {
    return m_Shaders;
}