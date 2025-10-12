#pragma once

#include <memory>

// Прямые объявления
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

    // Статические функции-обертки для колбэков GLFW
    // Статические "мосты" для системы колбэков GLFW
    static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos); // <--- ЭТА СТРОКА ДОЛЖНА БЫТЬ
};