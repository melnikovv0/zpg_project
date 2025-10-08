#include "Application.h"
#include "ShaderProgram.h"
#include "Model.h"
#include "DrawableObject.h"

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "CompositeTransform.h"
#include "Translation.h"
#include "Rotation.h"
#include "Scale.h"

static void error_callback(int, const char* description) { fputs(description, stderr); }

Application::Application(int width, int height, const char* title) {
    initGLFW(width, height, title);
    initGLEW();

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.f, 0.f, 0.f, 1.f);

    // --- шейдеры (вершинный с uniform mat4 modelMatrix) ---
    const char* vsrc =
        "#version 330 core\n"
        "layout(location=0) in vec3 aPos;\n"
        "layout(location=1) in vec3 aNormal;\n"
        "uniform mat4 modelMatrix;\n"
        "void main(){ gl_Position = modelMatrix * vec4(aPos, 1.0); }\n";

    const char* fsrc =
        "#version 330 core\n"
        "out vec4 fragColor;\n"
        "void main(){ fragColor = vec4(0.0, 1.0, 0.0, 1.0); }\n";

    progGreen = new ShaderProgram(vsrc, fsrc);

    // --- квадрат: pos(3) + normal(3) => 6 float на вершину ---
    std::vector<float> square = {
       -0.5f,-0.5f,0.0f,  0,0,1,
        0.5f,-0.5f,0.0f,  0,0,1,
        0.5f, 0.5f,0.0f,  0,0,1,

       -0.5f,-0.5f,0.0f,  0,0,1,
        0.5f, 0.5f,0.0f,  0,0,1,
       -0.5f, 0.5f,0.0f,  0,0,1,
    };
    modelSquare = new Model(square);

    // --- сцена: добавляем объект и сохраняем «ручку» на него ---
    auto& quad = scene.add(modelSquare, progGreen);
    quadObj = &quad;
}

Application::~Application() {
    scene.clear();

    delete modelSquare;
    delete progGreen;

    glfwDestroyWindow(window);
    glfwTerminate();
}

void Application::initGLFW(int w, int h, const char* title) {
    glfwSetErrorCallback(error_callback);
    if (!glfwInit()) std::exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(w, h, title, nullptr, nullptr);
    if (!window) { glfwTerminate(); std::exit(EXIT_FAILURE); }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

void Application::initGLEW() {
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) std::exit(EXIT_FAILURE);

    // запрошенный вывод GL-информации
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "GLSL: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void Application::run() { loop(); }

void Application::loop() {
    // Собрали цепочку: Scale -> Rotation (динамика через update) -> Translation
    auto chain = std::make_shared<CompositeTransform>();
    chain->add(std::make_shared<Scale>(glm::vec3(0.8f)));
    auto rot = std::make_shared<Rotation>(0.0f, glm::vec3(0, 0, 1));
    chain->add(rot);
    chain->add(std::make_shared<Translation>(glm::vec3(0.2f, 0.0f, 0.0f)));

    quadObj->setTransform(chain);

    double prev = glfwGetTime();

    while (!glfwWindowShouldClose(window)) {
        double now = glfwGetTime();
        float dt = static_cast<float>(now - prev);
        prev = now;

        // обновляем «живые» трансформации
        rot->setAngle(rot->getAngle() + 1.0f * dt); // 1 рад/сек

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        scene.update(dt);
        scene.render();

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
}
