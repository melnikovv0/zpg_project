#include "Application.h"
#include <iostream>
#include <vector>
using namespace std;

static void error_callback(int error, const char* description) {
    fputs(description, stderr);
}

Application::Application(int width, int height, const char* title)
    : window(nullptr)
{
    initGLFW(width, height, title);
    initGLEW();

    //triangle 
    const char* vertex_shader1 =
        "#version 330 core\n"
        "layout(location=0) in vec3 vp;\n"
        "void main() {\n"
        "    gl_Position = vec4(vp, 1.0);\n"
        "}\n";

    const char* fragment_shader1 =
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "    fragColor = vec4(0.0, 1.0, 0.0, 1.0); // green\n"
        "}\n";

    ShaderProgram* greenProgram = new ShaderProgram(vertex_shader1, fragment_shader1);

    //square 
    const char* vertex_shader2 =
        "#version 330 core\n"
        "layout(location=0) in vec3 vp;\n"
        "void main() {\n"
        "    gl_Position = vec4(vp, 1.0);\n"
        "}\n";

    const char* fragment_shader2 =
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "void main() {\n"
        "    fragColor = vec4(1.0, 0.0, 0.0, 1.0); // red\n"
        "}\n";

    ShaderProgram* redProgram = new ShaderProgram(vertex_shader2, fragment_shader2);


    vector<float> triangleVertices = {
        0.0f,  0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
       -0.5f, -0.5f, 0.0f
    };

    std::vector<float> squareVertices = {
      0.5f,  0.5f, 0.0f, 
      1.0f,  0.5f, 0.0f,
      1.0f,  0.0f, 0.0f,

      0.5f,  0.5f, 0.0f,
      1.0f,  0.0f, 0.0f,
      0.5f,  0.0f, 0.0f
    };


    models.push_back(new Model(triangleVertices));
    models.push_back(new Model(squareVertices));

    programs.push_back(greenProgram);
    programs.push_back(redProgram);




}

Application::~Application() {
    for (auto p : programs) {
        delete p;
    }
    for (auto m : models) {
        delete m;
    }

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::initGLFW(int width, int height, const char* title) {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) {
        fprintf(stderr, "ERROR: could not start GLFW3\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

void Application::initGLEW() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "ERROR: could not start GLEW\n");
        exit(EXIT_FAILURE);
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void Application::run() {
    loop();
}

void Application::loop() {
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        
        //  green triangle
        programs[0]->use();
        models[0]->draw();

        // red square
        programs[1]->use();
        models[1]->draw();


        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}
