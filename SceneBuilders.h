#pragma once

// Прямые объявления, чтобы не подключать полные заголовки
class Scene;
class ModelManager;
class ShaderManager;

namespace SceneBuilders {

    // Эта функция строит сцену №1: Вращающийся треугольник (Задача 5)
    void buildScene1(Scene& scene, ModelManager& models, ShaderManager& shaders);
    void buildScene2(Scene& scene, ModelManager& models, ShaderManager& shaders);

    void buildScene3(Scene& scene, ModelManager& models, ShaderManager& shaders);


}