#include "ApplicationController.h"
#include <iostream>
#include "SceneBuilders.h"
#include <GLFW/glfw3.h>

ApplicationController::ApplicationController(GLFWwindow* window, int width, int height)
    : window(window), m_width(width), m_height(height) {
}

ApplicationController::~ApplicationController() {}

void ApplicationController::init() {
    m_ModelManager.loadModels();
    m_ShaderManager.loadShaders();

    m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));

    m_Light = std::make_unique<Light>(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f));


    std::cout << "Building Scene 1..." << std::endl;
    SceneBuilders::buildScene1(scenes[1], m_ModelManager, m_ShaderManager);
    SceneBuilders::buildScene2(scenes[2], m_ModelManager, m_ShaderManager); 
    SceneBuilders::buildScene3(scenes[3], m_ModelManager, m_ShaderManager);

    switchScene(1);
;
}


void ApplicationController::update(float dt) {

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_Camera->processKeyboard(FORWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_Camera->processKeyboard(BACKWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_Camera->processKeyboard(LEFT, dt);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_Camera->processKeyboard(RIGHT, dt);

    std::cout << " Camera Pos: x=" << m_Camera->Position.x << ", z=" << m_Camera->Position.z << "\r";

    if (activeScene) {
        activeScene->update(dt);
    }
}

void ApplicationController::render() {

    if (activeScene && m_Camera && m_Light ) {


        glm::mat4 view = m_Camera->getViewMatrix();

        float aspectRatio = (m_width > 0 && m_height > 0) ? (float)m_width / (float)m_height : 1.0f;
        glm::mat4 projection = glm::perspective(glm::radians(m_Camera->Zoom), aspectRatio, 0.1f, 100.0f);

        glm::vec3 lightPos = m_Light->Position;
        glm::vec3 lightColor = m_Light->Color;
        glm::vec3 viewPos = m_Camera->Position;

        for (auto const& [name, shader] : m_ShaderManager.getAllShaders()) {
            shader->use();
            shader->setUniform("viewMatrix", view);
            shader->setUniform("projectionMatrix", projection);

            shader->setUniform("lightPos", lightPos);
            shader->setUniform("viewPos", viewPos);
            shader->setUniform("lightColor", lightColor);
        }

        activeScene->render();
    }
}

void ApplicationController::keyCallback(int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS) {
        if (key == GLFW_KEY_1) switchScene(1);
        else if (key == GLFW_KEY_2) switchScene(2);
        else if (key == GLFW_KEY_3) switchScene(3); 

        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, true);
    }
}

void ApplicationController::mouseCallback(double xpos, double ypos) {
    if (firstMouse) {
        lastMouseX = xpos;
        lastMouseY = ypos;
        firstMouse = false;
    }

    double xoffset = xpos - lastMouseX;
    double yoffset = lastMouseY - ypos;
    lastMouseX = xpos;
    lastMouseY = ypos;

    if (m_Camera) {
        m_Camera->processMouseMovement(static_cast<float>(xoffset), static_cast<float>(yoffset));
    }
}

void ApplicationController::scrollCallback(double xoffset, double yoffset) {
    if (m_Camera) {
        m_Camera->processMouseScroll(static_cast<float>(yoffset));
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