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
    Model* triangleModel = models.getModel("triangle");
    ShaderProgram* greenShader = shaders.getShader("green");

    auto& triangleObj = scene.add(triangleModel, greenShader);

    auto rotation = std::make_shared<Rotation>(0.0f, glm::vec3(0.0f, 1.0f, 0.0f)); 
    triangleObj.setTransform(rotation);

    scene.setUpdateCallback([rotation](float dt) {
        rotation->setAngle(rotation->getAngle() + 1.5f * dt); 
        });


}

void SceneBuilders::buildScene2(Scene& scene, ModelManager& models, ShaderManager& shaders) {
    // 1. Получаем все необходимые ресурсы
    Model* sphereModel = models.getModel("sphere");
    ShaderProgram* constantShader = shaders.getShader("constant");
    ShaderProgram* lambertShader = shaders.getShader("lambert");
    ShaderProgram* phongShader = shaders.getShader("phong");
    ShaderProgram* blinnShader = shaders.getShader("blinn");

<<<<<<< HEAD
    glm::vec3 positions[] = {
        glm::vec3(0.5f,  0.0f, 0.0f), 
        glm::vec3(-0.5f,  0.0f, 0.0f), 
        glm::vec3(0.0f,  0.5f, 0.0f), 
        glm::vec3(0.0f, -0.5f, 0.0f)  
    };
=======
    // 2. Определяем позиции для каждой сферы
    glm::vec3 posRight = glm::vec3(0.7f, 0.0f, 0.0f);
    glm::vec3 posLeft = glm::vec3(-0.7f, 0.0f, 0.0f);
    glm::vec3 posUp = glm::vec3(0.0f, 0.7f, 0.0f);
    glm::vec3 posDown = glm::vec3(0.0f, -0.7f, 0.0f);
>>>>>>> develop

    // 3. Задаем цвет для всех сфер
    glm::vec3 object_color = glm::vec3(0.0f, 0.5f, 1.0f);

    // --- Создаем каждую сферу по отдельности ---

    // Сфера СПРАВА (использует Lambert)
    auto& sphereRight = scene.add(sphereModel, lambertShader);
    glm::mat4 transformRight = glm::translate(glm::mat4(1.0f), posRight);
    transformRight = glm::scale(transformRight, glm::vec3(0.4f));
    sphereRight.setModelMatrix(transformRight);
    sphereRight.addUniform("objectColor", object_color);

    // Сфера СЛЕВА (использует Phong)
    auto& sphereLeft = scene.add(sphereModel, phongShader);
    glm::mat4 transformLeft = glm::translate(glm::mat4(1.0f), posLeft);
    transformLeft = glm::scale(transformLeft, glm::vec3(0.4f));
    sphereLeft.setModelMatrix(transformLeft);
    sphereLeft.addUniform("objectColor", object_color);

    // Сфера ВВЕРХУ (использует Blinn-Phong)
    auto& sphereUp = scene.add(sphereModel, blinnShader);
    glm::mat4 transformUp = glm::translate(glm::mat4(1.0f), posUp);
    transformUp = glm::scale(transformUp, glm::vec3(0.4f));
    sphereUp.setModelMatrix(transformUp);
    sphereUp.addUniform("objectColor", object_color);

    // Сфера ВНИЗУ (использует Constant для сравнения)
    auto& sphereDown = scene.add(sphereModel, constantShader);
    glm::mat4 transformDown = glm::translate(glm::mat4(1.0f), posDown);
    transformDown = glm::scale(transformDown, glm::vec3(0.4f));
    sphereDown.setModelMatrix(transformDown);
    sphereDown.addUniform("objectColor", object_color);
}

void SceneBuilders::buildScene3(Scene& scene, ModelManager& models, ShaderManager& shaders) {
<<<<<<< HEAD
=======
    // 1. Получаем ресурсы
>>>>>>> develop
    Model* treeModel = models.getModel("tree");
    Model* bushModel = models.getModel("bush");
    Model* planeModel = models.getModel("plain");


    ShaderProgram* normalShader = shaders.getShader("normal_color");
    ShaderProgram* groundShader = shaders.getShader("lambert");

    // Создаем равнину (землю)
    auto& planeObj = scene.add(planeModel, groundShader);

    glm::mat4 planeTransform = glm::scale(glm::mat4(1.0f), glm::vec3(20.0f));
    planeObj.setModelMatrix(planeTransform);

    planeObj.addUniform("objectColor", glm::vec3(0.0f, 0.8f, 0.0f)); // Травяной цвет

<<<<<<< HEAD
    std::random_device rd;  
    std::mt19937 gen(rd()); 

    std::uniform_real_distribution<> posDist(-20.0, 20.0);

    std::uniform_real_distribution<> scaleDist(0.8, 1.2);

=======
    // 2. Настраиваем генератор случайных чисел
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> posDist(-20.0, 20.0);
    std::uniform_real_distribution<> scaleDist(0.8, 1.2);
>>>>>>> develop
    std::uniform_real_distribution<> angleDist(0.0, 360.0);


    for (int i = 0; i < 50; ++i) {
        auto& treeObj = scene.add(treeModel, normalShader);

<<<<<<< HEAD
        float x = posDist(gen);
        float z = posDist(gen);
        float scale = scaleDist(gen);
        float angle = angleDist(gen);
=======
        // --- ИЗМЕНЕНО: Добавлено явное преобразование типов ---
        float x = static_cast<float>(posDist(gen));
        float z = static_cast<float>(posDist(gen));
        float scale = static_cast<float>(scaleDist(gen));
        float angle = static_cast<float>(angleDist(gen));
>>>>>>> develop

        auto chain = std::make_shared<CompositeTransform>();
        chain->add(std::make_shared<Scale>(glm::vec3(scale)));
<<<<<<< HEAD
        chain->add(std::make_shared<Rotation>(glm::radians(angle), glm::vec3(0, 1, 0))); 
        chain->add(std::make_shared<Translation>(glm::vec3(x, 0.0f, z))); 

=======
        chain->add(std::make_shared<Rotation>(glm::radians(angle), glm::vec3(0, 1, 0)));
        chain->add(std::make_shared<Translation>(glm::vec3(x, 0.0f, z)));
>>>>>>> develop
        treeObj.setTransform(chain);
    }

    for (int i = 0; i < 50; ++i) {
        auto& bushObj = scene.add(bushModel, normalShader);

        // --- ИЗМЕНЕНО: Добавлено явное преобразование типов ---
        float x = static_cast<float>(posDist(gen));
        float z = static_cast<float>(posDist(gen));
        float scale = static_cast<float>(scaleDist(gen));
        float angle = static_cast<float>(angleDist(gen));

        // Собираем трансформацию
        auto chain = std::make_shared<CompositeTransform>();
        chain->add(std::make_shared<Scale>(glm::vec3(scale)));
        chain->add(std::make_shared<Rotation>(glm::radians(angle), glm::vec3(0, 1, 0)));
        chain->add(std::make_shared<Translation>(glm::vec3(x, 0.0f, z)));
        bushObj.setTransform(chain);
    }
}

