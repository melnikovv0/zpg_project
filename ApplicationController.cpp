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
    m_TextureManager.loadTextures();

    m_Camera = std::make_unique<Camera>(glm::vec3(0.0f, 0.0f, 3.0f));

    switchScene(1);
}

void ApplicationController::update(float dt) {

    if (m_flashlight) {
        m_flashlight->setPosition(m_Camera->Position);
        m_flashlight->setDirection(m_Camera->Front);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        m_Camera->processKeyboard(FORWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        m_Camera->processKeyboard(BACKWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        m_Camera->processKeyboard(LEFT, dt);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        m_Camera->processKeyboard(RIGHT, dt);

    std::cout << "Camera Pos: x=" << m_Camera->Position.x << ", z=" << m_Camera->Position.z << "\r";

    if (activeScene) {
        activeScene->update(dt);
    }
}

void ApplicationController::render() {
    if (activeScene) {
        float aspectRatio;
        if (m_width > 0 && m_height > 0) {
            aspectRatio = (float)m_width / (float)m_height;
        }
        else {
            aspectRatio = 1.0f;
        }
        glm::mat4 projectionMatrix = glm::perspective(glm::radians(m_Camera->Zoom), aspectRatio, 0.1f, 100.0f);

        auto shaders = activeScene->getUniqueShaders();
        for (auto* shader : shaders) {
            if (!shader) continue;
            shader->use();
            shader->setUniform("projectionMatrix", projectionMatrix);
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


        if (key == GLFW_KEY_F && m_flashlight) { 
            m_flashlightOn = !m_flashlightOn; 
            if (m_flashlightOn) {
                m_flashlight->setColors(glm::vec3(0.05f), glm::vec3(0.8f), glm::vec3(1.0f));
            }
            else {
                m_flashlight->setColors(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(0.0f));
            }
        }
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

void ApplicationController::onWindowResize(int width, int height) {
    m_width = width;
    m_height = height;
}

void ApplicationController::switchScene(int sceneNumber) {
    m_lightManager.clear();
    scenes[sceneNumber].clear();

    m_flashlight = nullptr;

    if (sceneNumber == 1) {
        SceneBuilders::buildScene1(scenes[1], m_ModelManager, m_ShaderManager, *m_Camera, m_lightManager);
    }
    else if (sceneNumber == 2) {
        SceneBuilders::buildScene2(scenes[2], m_ModelManager, m_ShaderManager, *m_Camera, m_lightManager);
    }
    else if (sceneNumber == 3) { 
        SceneBuilders::buildScene3(scenes[3], m_ModelManager, m_ShaderManager, m_TextureManager, *m_Camera, m_lightManager);

        auto flashlight = std::make_unique<Light>(
            m_Camera->Position,
            m_Camera->Front,
            glm::cos(glm::radians(12.5f)),
            glm::cos(glm::radians(17.5f)),
            glm::vec3(0.05f),  // ambient
            glm::vec3(0.8f),  // diffuse
            glm::vec3(1.0f)   // specular
        );
        m_flashlight = m_lightManager.addLight(std::move(flashlight));
        m_flashlightOn = true;
    }
    activeScene = &scenes[sceneNumber];
    std::cout << "Switched to Scene " << sceneNumber << std::endl;
}