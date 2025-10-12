#pragma once

#include <map>
#include <memory>
#include <string>
#include <stdexcept>

#include "ShaderProgram.h"

class ShaderManager {
public:
    void loadShaders();

    ShaderProgram* getShader(const std::string& name);

    const std::map<std::string, std::unique_ptr<ShaderProgram>>& getAllShaders() const;

private:
    std::map<std::string, std::unique_ptr<ShaderProgram>> m_Shaders;
};