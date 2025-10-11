#include "SceneBuilders.h"

#include "Scene.h"
#include "ModelManager.h"
#include "ShaderManager.h"

#include "CompositeTransform.h"
#include "Rotation.h"
#include <glm/ext/matrix_transform.hpp>

void SceneBuilders::buildScene1(Scene& scene, ModelManager& models, ShaderManager& shaders) {
    // 1. Получаем ресурсы из менеджеров
    Model* triangleModel = models.getModel("triangle");
    ShaderProgram* greenShader = shaders.getShader("green");

    // 2. Создаем объект на сцене
    auto& triangleObj = scene.add(triangleModel, greenShader);

    // 3. Создаем для него анимацию вращения
    auto rotation = std::make_shared<Rotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)); // Вращение вокруг Y
    triangleObj.setTransform(rotation);

    // 4. Добавляем "поведение" в сцену, чтобы анимация работала
    //    Это лямбда-функция, которая будет вызываться каждый кадр для этой сцены
    scene.setUpdateCallback([rotation](float dt) {
        rotation->setAngle(rotation->getAngle() + 1.5f * dt); // 1.5 радиан в секунду
        });


}

void SceneBuilders::buildScene2(Scene& scene, ModelManager& models, ShaderManager& shaders) {
    // 1. Получаем необходимые ресурсы из менеджеров
    Model* sphereModel = models.getModel("sphere");
    ShaderProgram* normalShader = shaders.getShader("normal_color"); // Будут зеленые, как вы и хотели

    // 2. Определяем позиции для 4-х сфер: справа, слева, вверху, внизу
    glm::vec3 positions[] = {
        glm::vec3(0.5f,  0.0f, 0.0f), // Справа
        glm::vec3(-0.5f,  0.0f, 0.0f), // Слева
        glm::vec3(0.0f,  0.5f, 0.0f), // Вверху
        glm::vec3(0.0f, -0.5f, 0.0f)  // Внизу
    };

    // 3. Создаем 4 объекта в цикле
    for (int i = 0; i < 4; ++i) {
        // Создаем новый объект на сцене
        auto& sphereObj = scene.add(sphereModel, normalShader);

        // Создаем для него статичную матрицу трансформации
        // Сначала уменьшаем сферу (т.к. ее базовый размер 1.0), потом двигаем на позицию
        glm::mat4 staticMatrix = glm::translate(glm::mat4(1.0f), positions[i]);
        staticMatrix = glm::scale(staticMatrix, glm::vec3(0.3f)); // Уменьшаем до 30%

        // Устанавливаем эту матрицу для объекта
        sphereObj.setModelMatrix(staticMatrix);
    }
}
