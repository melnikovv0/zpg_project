#include "ApplicationController.h"
#include <iostream>
#include "SceneBuilders.h"
#include <GLFW/glfw3.h>

// Конструктор пока остается простым
ApplicationController::ApplicationController(GLFWwindow* window)
    : window(window) {
}

// Деструктор пока пустой, т.к. unique_ptr все чистит сам
ApplicationController::~ApplicationController() {}

void ApplicationController::init() {
    // 1. Говорим менеджерам загрузить все ресурсы
    m_ModelManager.loadModels();
    m_ShaderManager.loadShaders();

    // 2. Строим сцену №1

    std::cout << "Building Scene 1..." << std::endl;
    // scenes[1] создаст новую пустую сцену в map, если её там нет
    SceneBuilders::buildScene1(scenes[1], m_ModelManager, m_ShaderManager);
    SceneBuilders::buildScene2(scenes[2], m_ModelManager, m_ShaderManager); 

    // 3. Сразу делаем сцену №1 активной
    switchScene(1);
;
}

// ... остальные методы (update, render, keyCallback) пока остаются пустыми ...

void ApplicationController::update(float dt) {
    if (activeScene) {
        activeScene->update(dt);
    }
}

void ApplicationController::render() {
    if (activeScene) {
        // 1. Создаем "пустую" единичную матрицу
        glm::mat4 identityMatrix = glm::mat4(1.0f);

        // 2. "Обманываем" все шейдеры, отправляя им эту пустую матрицу
        //    в качестве view и projection.
        for (auto const& [name, shader] : m_ShaderManager.getAllShaders()) {
            shader->use();
            shader->setUniform("viewMatrix", identityMatrix);
            shader->setUniform("projectionMatrix", identityMatrix);
        }

        // 3. Рисуем активную сцену (как и раньше)
        activeScene->render();
    }
}

void ApplicationController::keyCallback(int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_1) {
            switchScene(1);
        }
        
         else if (key == GLFW_KEY_2) {
             switchScene(2);
         }
    }
}

void ApplicationController::switchScene(int sceneNumber) {
    auto it = scenes.find(sceneNumber);
    if (it != scenes.end()) {
        activeScene = &it->second;
        std::cout << "Switched to Scene " << sceneNumber << std::endl;
    }
    else {
        std::cout << "Scene " << sceneNumber << " is not built!" << std::endl;
    }
}