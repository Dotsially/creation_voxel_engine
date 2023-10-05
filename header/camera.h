#pragma once
#include "depedencies.h"
#include "SDL2/SDL.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/vector_angle.hpp"
#include <iostream>


enum CameraType{
    CAMERA_THIRDPERSON,
    CAMERA_FIRSTPERSON,
    CAMERA_FREECAM
};

class Camera{
    glm::vec3 position;
    glm::vec3 target;
    glm::vec3 worldUp;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 moveDirection;
    glm::vec2 lastMouse;
    bool firstMove = false;
    f32 fov;
    f32 yaw;
    f32 pitch;
    CameraType cameraType;

public:
    Camera(CameraType type, glm::vec3 position);
    ~Camera();
    void Update(const u8* keystate, glm::vec3 targetPosition);
    glm::mat4 GetProjectMatrix();
    glm::mat4 GetViewMatrix();
    glm::vec3 GetPosition();
    glm::vec3 GetTarget();
};