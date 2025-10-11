#include "ShaderManager.h"
void ShaderManager::loadShaders() {
    // --- Шейдер 1: Простой зеленый цвет ---
    const char* vsrc_simple =
        "#version 330 core\n"
        "layout(location=0) in vec3 aPos;\n"
        "uniform mat4 modelMatrix;\n"
        "void main(){ gl_Position = modelMatrix * vec4(aPos, 1.0); }\n";

    const char* fsrc_green =
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "void main(){ fragColor = vec4(0.0, 1.0, 0.0, 1.0); }\n";

    // Создаем программу и сохраняем ее под именем "green"
    m_Shaders["green"] = std::make_unique<ShaderProgram>(vsrc_simple, fsrc_green);


    // --- Шейдер 2: Простой синий цвет ---
    const char* fsrc_blue =
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "void main(){ fragColor = vec4(0.0, 0.5, 1.0, 1.0); }\n";

    // Создаем программу и сохраняем ее под именем "blue"
    // Вершинный шейдер используем тот же самый!
    m_Shaders["blue"] = std::make_unique<ShaderProgram>(vsrc_simple, fsrc_blue);


    const char* vsrc_normal_color =
        "#version 330 core\n"
        "layout(location=0) in vec3 aPos;\n"
        "layout(location=1) in vec3 aNormal;\n" // Принимаем нормаль
        "uniform mat4 modelMatrix;\n"
        "uniform mat4 viewMatrix;\n"
        "uniform mat4 projectionMatrix;\n"
        "out vec3 fragNormal;\n" // Передаем нормаль во фрагментный шейдер
        "void main(){\n"
        "    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPos, 1.0);\n"
        "    fragNormal = mat3(transpose(inverse(modelMatrix))) * aNormal;\n" // Трансформируем нормаль
        "}\n";

    const char* fsrc_normal_color =
        "#version 330 core\n"
        "in vec3 fragNormal;\n" // Получаем нормаль из вершинного шейдера
        "out vec4 fragColor;\n"
        "void main(){\n"
        "    vec3 norm = normalize(fragNormal);\n" // Нормализуем на всякий случай
        "    vec3 color = (norm + 1.0) / 2.0;\n" // Та самая формула!
        "    fragColor = vec4(color, 1.0);\n"
        "}\n";

    // Создаем программу и сохраняем ее под именем "normal_color"
    m_Shaders["normal_color"] = std::make_unique<ShaderProgram>(vsrc_normal_color, fsrc_normal_color);
}

ShaderProgram* ShaderManager::getShader(const std::string& name) {
    // Ищем программу в нашем хранилище по имени
    auto it = m_Shaders.find(name);

    // Проверяем, нашли ли мы её
    if (it != m_Shaders.end()) {
        // Если да, возвращаем обычный указатель на программу.
        return it->second.get();
    }

    // Если программа не найдена, сообщаем об ошибке
    throw std::runtime_error("ShaderManager Error: Shader program not found: " + name);
}

// --- ДОБАВЬТЕ РЕАЛИЗАЦИЮ ЭТОГО МЕТОДА ---
const std::map<std::string, std::unique_ptr<ShaderProgram>>& ShaderManager::getAllShaders() const {
    // Просто возвращаем ссылку на наше внутреннее хранилище шейдеров
    return m_Shaders;
}