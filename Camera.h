﻿#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

#include "ISubject.h"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 130.0f;


class Camera : public ISubject {
public:
 
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
  
    float Yaw;
    float Pitch;
  
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    
    explicit Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

   
    glm::mat4 getViewMatrix();

  
    void processKeyboard(Camera_Movement direction, float deltaTime);

  
    void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

 
    void processMouseScroll(float yoffset);


private:
   
    void updateCameraVectors();
};