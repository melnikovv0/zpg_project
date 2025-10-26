#include "ShaderManager.h"
#include <string> 

void ShaderManager::loadShaders() {

    std::string shader_path = "";

    std::string vs_lighting_path = shader_path + "vertex_shader_lighting_transform.glsl";

    m_Shaders["phong"] = std::make_unique<ShaderProgram>(vs_lighting_path, shader_path + "fragment_shader_phong.glsl");
    m_Shaders["blinn"] = std::make_unique<ShaderProgram>(vs_lighting_path, shader_path + "fragment_shader_blinn.glsl");
    m_Shaders["lambert"] = std::make_unique<ShaderProgram>(vs_lighting_path, shader_path + "fragment_shader_lambert.glsl");
    m_Shaders["constant"] = std::make_unique<ShaderProgram>(vs_lighting_path, shader_path + "fragment_shader_constant.glsl");

    m_Shaders["phong_multi"] = std::make_unique<ShaderProgram>(vs_lighting_path, shader_path + "fragment_shader_phong_multi.glsl");

    m_Shaders["normal_color"] = std::make_unique<ShaderProgram>(shader_path + "vertex_shader_normal_transform.glsl", shader_path + "fragment_shader_normal_visualizer.glsl");



    m_Shaders["green"] = std::make_unique<ShaderProgram>(shader_path + "vertex_shader_simple_transform.glsl", shader_path + "fragment_shader_green.glsl");

    

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