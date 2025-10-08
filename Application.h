#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.h"

class ShaderProgram;
class Model;
class DrawableObject;

class Application {
public:
    Application(int width, int height, const char* title);
    ~Application();

    void run();

private:
    GLFWwindow* window = nullptr;

    void initGLFW(int width, int height, const char* title);
    void initGLEW();
    void loop();

    Scene scene;                     // сцена как поле

    ShaderProgram* progGreen = nullptr;
    Model* modelSquare = nullptr;

    // «ручка» на объект квадрата + угол вращения
    DrawableObject* quadObj = nullptr;
    float angle = 0.0f;
};
