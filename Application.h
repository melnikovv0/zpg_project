#pragma once

#include <memory>

struct GLFWwindow;
class ApplicationController;

class Application {
public:
    Application(int width, int height, const char* title);
    ~Application();

    void run();

private:
    void initGLFW(int width, int height, const char* title);
    void initGLEW();

    GLFWwindow* m_Window = nullptr;
    std::unique_ptr<ApplicationController> m_Controller;


    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos); 
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};