#include "Camera.hpp"

Camera::Camera(CameraParameters& parameters)
        : m_Parameters(parameters), m_CameraPosition(parameters.position), m_CameraDirection(parameters.direction),
          m_CameraUp(parameters.up), m_RotationAngle(parameters.rotation_angle), m_Fov(parameters.fov), m_Sensitivity(parameters.sensitivity) {

    m_Model = glm::mat4(1.0f);
    m_View = glm::mat4(1.0f);
    m_Projection = glm::mat4(1.0f);
    m_LookAt = glm::mat4(1.0f);
    m_Yaw = -90.0f;
    m_Pitch = 0.0f;
    UpdateCameraVector();
}

glm::mat4 Camera::GetViewMatrix() const {
    return glm::lookAt(m_CameraPosition, m_CameraPosition + m_CameraDirection, m_CameraUp);
}

void Camera::Reset() {
    m_CameraPosition = m_Parameters.position;
    m_CameraDirection = m_Parameters.direction;
    m_CameraUp = m_Parameters.up;
    m_RotationAngle = m_Parameters.rotation_angle;
    m_Fov = m_Parameters.fov;
    m_Sensitivity = m_Parameters.sensitivity;
    m_Yaw = -90.0f;
    m_Pitch = 0.0f;
    UpdateCameraVector();
}

void Camera::WalkAround() {
    ImGuiIO& io = ImGui::GetIO();
    m_Fov = std::clamp(m_Fov + io.MouseWheel, 1.0f, 45.0f);
    int rotation_direction = 1;
    if (io.KeysDown[ImGuiKey_W]) {
        m_CameraPosition += m_Sensitivity * m_CameraDirection;
    }
    if (io.KeysDown[ImGuiKey_A]) {
        m_CameraPosition -= m_Sensitivity * m_CameraRight;
    }
    if (io.KeysDown[ImGuiKey_S]) {
        m_CameraPosition -= m_Sensitivity * m_CameraDirection;
    }
    if (io.KeysDown[ImGuiKey_D]) {
        m_CameraPosition += m_Sensitivity * m_CameraRight;
    }
    if (io.KeysDown[ImGuiKey_LeftCtrl] && io.KeysDown[ImGuiKey_Q]) {
        rotation_direction = -1;
    }
    if (io.KeysDown[ImGuiKey_Q]) {
        m_RotationAngle += 10.0f * m_Sensitivity * rotation_direction;
        m_RotationAngle = fmod(m_RotationAngle + 360.0f, 360.0f);
    }
    if (io.KeysDown[ImGuiKey_R]) {
        Reset();
    }

}

void Camera::GetDelta() {
    // Get the mouse drag delta
    float deltaX = ImGui::GetMouseDragDelta().x;
    float deltaY = ImGui::GetMouseDragDelta().y;
    float sensitivity = 0.1f;

    m_Yaw += sensitivity * deltaX; // Invert if necessary
    m_Pitch += -sensitivity * deltaY;
    m_Pitch = glm::clamp(m_Pitch, -89.0f, 89.0f);
    UpdateCameraVector();
    ImGui::ResetMouseDragDelta();

}

void Camera::UpdateCameraVector() {
    // calculate the new Front vector
    glm::vec3 front;

    front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    front.y = sin(glm::radians(m_Pitch));
    front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

    m_CameraDirection = glm::normalize(front);
    m_CameraRight = glm::normalize(glm::cross(m_CameraDirection, m_Parameters.up)); // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_CameraUp = glm::normalize(glm::cross(m_CameraRight, m_CameraDirection));
}

void Camera::Update() {
    WalkAround();
    GetDelta();
}
