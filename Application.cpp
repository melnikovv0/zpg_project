#include "Application.h"
#include "ApplicationController.h"

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <memory>                  // Дstd::unique_ptr , std::make_unique
#include <stdexcept>               //  std::runtime_error
#include <GLFW/glfw3.h>




Application::Application(int width, int height, const char* title) {
    initGLFW(width, height, title);
    initGLEW();

<<<<<<< HEAD
    m_Controller = std::make_unique<ApplicationController>(m_Window);
=======
    // Создаем наш контроллер. unique_ptr позаботится о его удалении.
    m_Controller = std::make_unique<ApplicationController>(m_Window, width, height);
>>>>>>> develop


    glfwSetWindowUserPointer(m_Window, m_Controller.get());

    glfwSetKeyCallback(m_Window, Application::keyCallback);
    glfwSetCursorPosCallback(m_Window, Application::mouseCallback);
   
}

Application::~Application() {
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void Application::run() {
    m_Controller->init();

    double prevTime = glfwGetTime();

    while (!glfwWindowShouldClose(m_Window)) {
        double currentTime = glfwGetTime();
        float dt = static_cast<float>(currentTime - prevTime);
        prevTime = currentTime;

        glClearColor(0.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_Controller->update(dt);
        m_Controller->render();

        glfwSwapBuffers(m_Window);
        glfwPollEvents();
    }
}


void Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    auto* controller = static_cast<ApplicationController*>(glfwGetWindowUserPointer(window));
    if (controller) {
        controller->keyCallback(key, scancode, action, mods);
    }
}

void Application::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    auto* controller = static_cast<ApplicationController*>(glfwGetWindowUserPointer(window));
    if (controller) {
        controller->mouseCallback(xpos, ypos);
    }
}



void Application::initGLFW(int width, int height, const char* title) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!m_Window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(m_Window);
    glfwSwapInterval(1);
    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); 
}

void Application::initGLEW() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        throw std::runtime_error("Failed to initialize GLEW");
    }
    glEnable(GL_DEPTH_TEST);

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
}
