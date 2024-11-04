#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include <iostream>
#include <algorithm>

struct CameraParameters {
    float SCREEN_WIDTH;
    float SCREEN_HEIGHT;
    glm::vec3 position;
    glm::vec3 direction;
    glm::vec3 up;
    float rotation_angle;
    float fov;
    float sensitivity;
};

class Camera {
public:
    Camera(CameraParameters &parameter);
    glm::mat4 GetViewMatrix() const;
    void Reset();
    void WalkAround();
    void Update();
    void GetDelta();
    void UpdateCameraVector();
    ~Camera() = default;

public:
    CameraParameters m_Parameters;
    glm::vec3 m_CameraPosition;
    glm::vec3 m_CameraDirection;
    float m_RotationAngle;
    float m_Fov;
    float m_Sensitivity;

public:
    glm::mat4 m_Model;
    glm::mat4 m_View;
    glm::mat4 m_Projection;
    glm::mat4 m_LookAt;
    float m_Yaw;
    float m_Pitch;
    glm::vec3 m_CameraRight;
    glm::vec3 m_CameraUp;
};
