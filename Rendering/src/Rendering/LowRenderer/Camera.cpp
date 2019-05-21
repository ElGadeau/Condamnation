#include "stdafx.h"
#include <Rendering/LowRenderer/Camera.h>
#include <glm/gtc/matrix_transform.hpp>

Rendering::LowRenderer::Camera::Camera(glm::vec3 p_position, glm::vec3 p_up, float p_yaw,
    float p_pitch)
: m_front(glm::vec3(0.0f, 0.0f, 0.0f)), m_movementSpeed(SPEED), m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM)
{
    m_position = p_position;
    m_worldUp = p_up;
    m_yaw = p_yaw;
    m_pitch = p_pitch;
    UpdateCameraVectors();
}

Rendering::LowRenderer::Camera::Camera(float p_posX, float p_posY, float p_posZ,
    float p_upX, float p_upY, float p_upZ, float p_yaw, float p_pitch)
    : m_front(glm::vec3(0.0f, 0.0f, 1.0f)), m_movementSpeed(SPEED), m_mouseSensitivity(SENSITIVITY), m_zoom(ZOOM)
{
    m_position = glm::vec3(p_posX, p_posY, p_posZ);
    m_worldUp = glm::vec3(p_upX, p_upY, p_upZ);
    m_yaw = p_yaw;
    m_pitch = p_pitch;
    UpdateCameraVectors();
}

glm::mat4 Rendering::LowRenderer::Camera::GetViewMatrix()
{
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Rendering::LowRenderer::Camera::GetPerspectiveMatrix()
{
    return glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 1000000.0f);
}

void Rendering::LowRenderer::Camera::UpdateCameraVectors()
{
    //calculate front
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    front.y = sin(glm::radians(m_pitch));
    front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    m_front = glm::normalize(front);

    //calculate right and up
    m_right = glm::normalize(glm::cross(m_front, m_worldUp));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
