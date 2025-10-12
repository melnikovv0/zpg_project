#include "SceneBuilders.h"

#include "Scene.h"
#include "ModelManager.h"
#include "ShaderManager.h"

#include "CompositeTransform.h"
#include "Rotation.h"
#include <glm/ext/matrix_transform.hpp>
#include <random>
#include "Translation.h"
#include "Scale.h"

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
    Model* sphereModel = models.getModel("sphere");
    ShaderProgram* normalShader = shaders.getShader("normal_color"); 

    glm::vec3 positions[] = {
        glm::vec3(0.5f,  0.0f, 0.0f), // Справа
        glm::vec3(-0.5f,  0.0f, 0.0f), // Слева
        glm::vec3(0.0f,  0.5f, 0.0f), // Вверху
        glm::vec3(0.0f, -0.5f, 0.0f)  // Внизу
    };

    for (int i = 0; i < 4; ++i) {
        auto& sphereObj = scene.add(sphereModel, normalShader);

  
        glm::mat4 staticMatrix = glm::translate(glm::mat4(1.0f), positions[i]);
        staticMatrix = glm::scale(staticMatrix, glm::vec3(0.3f)); 

        sphereObj.setModelMatrix(staticMatrix);
    }

}
void SceneBuilders::buildScene3(Scene& scene, ModelManager& models, ShaderManager& shaders) {
    // 1. Получаем ресурсы, которые будем многократно использовать
    Model* treeModel = models.getModel("tree");
    Model* bushModel = models.getModel("bush");
    ShaderProgram* normalShader = shaders.getShader("normal_color");

    // 2. Настраиваем генератор случайных чисел
    std::random_device rd;  // Источник энтропии
    std::mt19937 gen(rd()); // Генератор
    // Распределение для позиций X и Z (например, в квадрате от -10 до 10)
    std::uniform_real_distribution<> posDist(-20.0, 20.0);
    // Распределение для масштаба (например, от 80% до 120% от базового размера)
    std::uniform_real_distribution<> scaleDist(0.8, 1.2);
    // Распределение для угла поворота (от 0 до 360 градусов)
    std::uniform_real_distribution<> angleDist(0.0, 360.0);

    // 3. Генерируем 50 деревьев
    for (int i = 0; i < 50; ++i) {
        auto& treeObj = scene.add(treeModel, normalShader);

        // Генерируем случайные параметры
        float x = posDist(gen);
        float z = posDist(gen);
        float scale = scaleDist(gen);
        float angle = angleDist(gen);

        // Собираем трансформацию
        auto chain = std::make_shared<CompositeTransform>();
        chain->add(std::make_shared<Scale>(glm::vec3(scale)));
        chain->add(std::make_shared<Rotation>(glm::radians(angle), glm::vec3(0, 1, 0))); // Вращение вокруг Y
        chain->add(std::make_shared<Translation>(glm::vec3(x, 0.0f, z))); // Ставим на плоскость XZ

        treeObj.setTransform(chain);
    }

    // 4. Генерируем 50 кустов
    for (int i = 0; i < 50; ++i) {
        auto& bushObj = scene.add(bushModel, normalShader);

        float x = posDist(gen);
        float z = posDist(gen);
        float scale = scaleDist(gen);
        float angle = angleDist(gen);

        auto chain = std::make_shared<CompositeTransform>();
        chain->add(std::make_shared<Scale>(glm::vec3(scale)));
        chain->add(std::make_shared<Rotation>(glm::radians(angle), glm::vec3(0, 1, 0)));
        chain->add(std::make_shared<Translation>(glm::vec3(x, 0.0f, z)));

        bushObj.setTransform(chain);
    }
}

