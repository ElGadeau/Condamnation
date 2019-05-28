#include "stdafx.h"
#include <Rendering/LowRenderer/Camera.h>
#include <glm/gtc/matrix_transform.hpp>

Rendering::LowRenderer::Camera::Camera(const glm::vec3& p_position, const glm::vec3& p_up,
                                       const float&     p_yaw,      const float&     p_pitch)
{
    m_position = p_position;
    m_worldUp  = p_up;
    m_yaw      = p_yaw;
    m_pitch    = p_pitch;
    UpdateCameraVectors();
}

Rendering::LowRenderer::Camera::Camera(const float& p_posX, const float& p_posY,const float& p_posZ,
                                       const float& p_upX, const float& p_upY, const float& p_upZ,
                                       const float& p_yaw, const float& p_pitch)
{
    m_position = glm::vec3(p_posX, p_posY, p_posZ);
    m_worldUp  = glm::vec3(p_upX, p_upY, p_upZ);
    m_yaw      = p_yaw;
    m_pitch    = p_pitch;
    UpdateCameraVectors();
}

void Rendering::LowRenderer::Camera::UpdateCameraVectors()
{
    //calculate front
    glm::vec<3, double> front;
    front.x = cos(glm::radians(m_pitch)) * cos(glm::radians(m_yaw));
    front.y = sin(glm::radians(m_pitch));
    front.z = cos(glm::radians(m_pitch)) * sin(glm::radians(m_yaw));
    m_front = normalize(front);

    //calculate right and up
    m_right = normalize(cross(m_front, m_worldUp));
    m_up    = normalize(cross(m_right, m_front));
}
