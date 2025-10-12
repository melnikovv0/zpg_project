#pragma once

#include <map>
#include <memory>
#include "Scene.h"
#include "ModelManager.h"    // <--- ДОБАВЛЯЕМ
#include "ShaderManager.h"   // <--- ДОБАВЛЯЕМ
#include "Camera.h" // <--- Подключаем камеру

class Model;
class ShaderProgram;
struct GLFWwindow;

class ApplicationController {
public:
    explicit ApplicationController(GLFWwindow* window);
    ~ApplicationController();

    ApplicationController(const ApplicationController&) = delete;
    ApplicationController& operator=(const ApplicationController&) = delete;

    void init();
    void update(float dt);
    void render();
    void keyCallback(int key, int scancode, int action, int mods);

    void mouseCallback(double xpos, double ypos);

    void scrollCallback(double xoffset, double yoffset);

private:
    void switchScene(int sceneNumber);

    GLFWwindow* window;
    int m_width;
    int m_height;

    std::map<int, Scene> scenes;
    Scene* activeScene = nullptr;

    // --- ДОБАВЛЕНО: Менеджеры ресурсов ---
    ModelManager  m_ModelManager;
    ShaderManager m_ShaderManager;
    std::unique_ptr<Camera> m_Camera;

    // --- Переменные для управления мышью ---
    double lastMouseX = 0.0;
    double lastMouseY = 0.0;
    bool firstMouse = true;
};