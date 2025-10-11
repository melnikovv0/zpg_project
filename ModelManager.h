#pragma once

#include <map>
#include <memory>
#include <string>
#include <stdexcept> // Для исключений

#include "Model.h"

class ModelManager {
public:
    // Загружает все стартовые модели (пока что из кода)
    void loadModels();

    // Предоставляет доступ к модели по имени
    Model* getModel(const std::string& name);

private:
    // Наше хранилище моделей: "имя" -> "указатель на модель"
    std::map<std::string, std::unique_ptr<Model>> m_Models;
};