#include "Shader.h"

// Добавляем необходимые заголовки для работы с файлами и ошибками
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

// Конструктор, который читает шейдер из файла
Shader::Shader(const std::string& filepath, GLenum shaderType) {
    // 1. Чтение файла
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("ERROR: Unable to open shader file: " + filepath);
    }

    std::stringstream buffer;
    buffer << file.rdbuf(); // Читаем все содержимое файла в буфер
    std::string shaderCode = buffer.str();
    const char* src = shaderCode.c_str();

    // 2. Компиляция шейдера
    shaderId = glCreateShader(shaderType);
    glShaderSource(shaderId, 1, &src, nullptr);
    glCompileShader(shaderId);

    // 3. Проверка на ошибки компиляции (ВАЖНО!)
    GLint success;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shaderId, 512, NULL, infoLog);
        // Выбрасываем исключение, чтобы программа остановилась с понятной ошибкой
        throw std::runtime_error("ERROR: Shader compilation failed for " + filepath + "\n" + infoLog);
    }
}

// Деструктор
Shader::~Shader() {
    if (shaderId != 0) {
        glDeleteShader(shaderId);
    }
}

// Метод для получения ID шейдера (нужен для ShaderProgram)
GLuint Shader::getShaderId() const {
    return shaderId;
}