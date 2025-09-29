#ifndef APPLICATION_H
#define APPLICATION_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector> 
#include "ShaderProgram.h"
#include "Model.h"

class Application {
public:
    Application(int width, int height, const char* title);
    ~Application();

    void run();

private:
    GLFWwindow* window;

    std::vector<Model*> models;
    std::vector<ShaderProgram*> programs;


    void initGLFW(int width, int height, const char* title);
    void initGLEW();
    void loop();
};

#endif
