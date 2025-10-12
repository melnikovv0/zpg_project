#include "Camera.h"
#include <iostream>

// Конструктор
Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM) {
    Position = position;
    WorldUp = up;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors(); // Сразу вычисляем все векторы при создании
}

// Возвращает матрицу вида (View Matrix)
glm::mat4 Camera::getViewMatrix() {
    // Камера находится в 'Position', смотрит в точку 'Position + Front', "верх" камеры - это вектор 'Up'
    return glm::lookAt(Position, Position + Front, Up);
}

// Обработка нажатий клавиш (WASD)
void Camera::processKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime; // Скорость, не зависящая от FPS
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}

// Обработка движения мыши
void Camera::processMouseMovement(float xoffset, float yoffset, bool constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // Ограничиваем угол Pitch, чтобы камера не переворачивалась вверх ногами
    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // Обновляем векторы Front, Right и Up на основе новых углов
    updateCameraVectors();
}

// Обработка колесика мыши (зум)
void Camera::processMouseScroll(float yoffset) {
    Zoom -= yoffset;
    // Ограничиваем зум
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

// Приватный метод для пересчета векторов
void Camera::updateCameraVectors() {
    // Вычисляем новый вектор Front на основе углов Yaw и Pitch
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);

    // Также пересчитываем вектор Right и Up
    // glm::cross - векторное произведение
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}