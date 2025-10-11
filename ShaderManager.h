#pragma once

#include <map>
#include <memory>
#include <string>
#include <stdexcept>

#include "ShaderProgram.h"

class ShaderManager {
public:
    // Загружает и компилирует все необходимые шейдеры
    void loadShaders();

    // Предоставляет доступ к шейдерной программе по имени
    ShaderProgram* getShader(const std::string& name);

    const std::map<std::string, std::unique_ptr<ShaderProgram>>& getAllShaders() const;

private:
    // Хранилище: "имя" -> "умный указатель на программу"
    std::map<std::string, std::unique_ptr<ShaderProgram>> m_Shaders;
};