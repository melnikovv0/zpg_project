#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

// Определяем возможные направления движения для камеры
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Параметры камеры по умолчанию
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;


class Camera {
public:
    // Параметры камеры
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Углы Эйлера
    float Yaw;
    float Pitch;
    // Настройки камеры
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // Конструктор с векторами
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

    // Возвращает матрицу вида, вычисленную с помощью углов Эйлера и матрицы LookAt
    glm::mat4 getViewMatrix();

    // Обрабатывает ввод с клавиатуры
    void processKeyboard(Camera_Movement direction, float deltaTime);

    // Обрабатывает ввод с мыши
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    // Обрабатывает ввод с колесика мыши (для зума)
    void processMouseScroll(float yoffset);

private:
    // Вычисляет векторы Front, Right и Up на основе обновленных углов Эйлера
    void updateCameraVectors();
};