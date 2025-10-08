/*
//GLEW 
#include <GL/glew.h>

//  GLFW
#include <GLFW/glfw3.h>

//  GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// 
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

static void error_callback(int error, const char* description) { fputs(description, stderr); }

// глобальная переменная направления
float rotationDirection = 1.0f;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        if (key == GLFW_KEY_ESCAPE)
            glfwSetWindowShouldClose(window, GLFW_TRUE);

        if (key == GLFW_KEY_SPACE) // пробел переключает направление
            rotationDirection *= -1.0f;

        printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
    }
}

static void window_focus_callback(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }
static void window_iconify_callback(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }
static void window_size_callback(GLFWwindow* window, int width, int height) {
    printf("resize %d, %d \n", width, height);
    glViewport(0, 0, width, height);
}
static void cursor_callback(GLFWwindow* window, double x, double y) { printf("cursor_callback \n"); }
static void button_callback(GLFWwindow* window, int button, int action, int mode) {
    if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

// GLM test
glm::mat4 Projection = glm::perspective(45.0f, 4.0f / 3.0f, 0.01f, 100.0f);
glm::mat4 View = glm::lookAt(
    glm::vec3(10, 10, 10),
    glm::vec3(0, 0, 0),
    glm::vec3(0, 1, 0)
);
glm::mat4 Model = glm::mat4(1.0f);

int main(void)
{
    GLFWwindow* window;
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);
    window = glfwCreateWindow(640, 480, "ZPG", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

    // callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetCursorPosCallback(window, cursor_callback);
    glfwSetMouseButtonCallback(window, button_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetWindowIconifyCallback(window, window_iconify_callback);
    glfwSetWindowSizeCallback(window, window_size_callback);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    float ratio = width / (float)height;
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);

    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(-0.5f, 0.5f, 0.f);

        glRotatef((float)glfwGetTime() * 50.f * rotationDirection, 0.f, 0.f, 1.f);

        glTranslatef(-0.5f, 0.5f, 0.f);

        glBegin(GL_QUADS);
        glColor3f(1.f, 0.f, 0.f);
        glVertex3f(0.5f, -0.5f, 0.f); q

            glColor3f(0.f, 1.f, 0.f);
        glVertex3f(-0.5f, -0.5f, 0.f);

        glColor3f(0.f, 0.f, 1.f);
        glVertex3f(-0.5f, 0.5f, 0.f);

        glColor3f(1.f, 1.f, 0.f);
        glVertex3f(0.5f, 0.5f, 0.f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}*/
