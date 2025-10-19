#include "ShaderManager.h"
#include <string> // Подключаем для использования std::string

void ShaderManager::loadShaders() {
<<<<<<< HEAD
    const char* vsrc_simple =
        "#version 330 core\n"
        "layout(location=0) in vec3 aPos;\n"
        "uniform mat4 modelMatrix;\n"
        "void main(){ gl_Position = modelMatrix * vec4(aPos, 1.0); }\n";
=======
    // Определяем путь к папке с шейдерами, чтобы не повторяться
    std::string shader_path = "";
>>>>>>> develop

    // --- Загружаем все шейдеры, просто указывая пути к файлам ---

<<<<<<< HEAD
    m_Shaders["green"] = std::make_unique<ShaderProgram>(vsrc_simple, fsrc_green);
=======
    // 1. Простой зеленый шейдер (для треугольника)
    // Он не нуждается в нормалях, поэтому использует простой вершинный шейдер
    m_Shaders["green"] = std::make_unique<ShaderProgram>(shader_path + "simple.vert", shader_path + "green.frag");
>>>>>>> develop

    // 2. Шейдер для отображения нормалей (для отладки)
    m_Shaders["normal_color"] = std::make_unique<ShaderProgram>(shader_path + "normal_color.vert", shader_path + "normal_color.frag");

<<<<<<< HEAD
    const char* fsrc_blue =
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "void main(){ fragColor = vec4(0.0, 0.5, 1.0, 1.0); }\n";

    m_Shaders["blue"] = std::make_unique<ShaderProgram>(vsrc_simple, fsrc_blue);


    const char* vsrc_normal_color =
        "#version 330 core\n"
        "layout(location=0) in vec3 aPos;\n"
        "layout(location=1) in vec3 aNormal;\n"
        "uniform mat4 modelMatrix;\n"
        "uniform mat4 viewMatrix;\n"
        "uniform mat4 projectionMatrix;\n"
        "out vec3 fragNormal;\n" 
        "void main(){\n"
        "    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);\n"
        "    fragNormal = mat3(transpose(inverse(modelMatrix))) * aNormal;\n" 
        "}\n";

    const char* fsrc_normal_color =
        "#version 330 core\n"
        "in vec3 fragNormal;\n" 
        "out vec4 fragColor;\n"
        "void main(){\n"
        "    vec3 norm = normalize(fragNormal);\n" 
        "    vec3 color = (norm + 1.0) / 2.0;\n" 
        "    fragColor = vec4(color, 1.0);\n"
        "}\n";

    m_Shaders["normal_color"] = std::make_unique<ShaderProgram>(vsrc_normal_color, fsrc_normal_color);
=======
    // 3. Шейдеры для моделей освещения (используют один и тот же вершинный шейдер)
    std::string vs_lighting_path = shader_path + "phong.vert";
    m_Shaders["constant"] = std::make_unique<ShaderProgram>(vs_lighting_path, shader_path + "constant.frag");
    m_Shaders["lambert"] = std::make_unique<ShaderProgram>(vs_lighting_path, shader_path + "lambert.frag");

    m_Shaders["phong"] = std::make_unique<ShaderProgram>(vs_lighting_path, shader_path + "phong.frag");
    m_Shaders["blinn"] = std::make_unique<ShaderProgram>(vs_lighting_path, shader_path + "blinn.frag");

    
>>>>>>> develop
}

// Методы getShader() и getAllShaders() остаются БЕЗ ИЗМЕНЕНИЙ.
// Их работа не зависит от того, как были загружены шейдеры.

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