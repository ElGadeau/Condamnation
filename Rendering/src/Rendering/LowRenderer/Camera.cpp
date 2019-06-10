#include "stdafx.h"

#include <glm/gtc/matrix_transform.hpp>

#include <Rendering/LowRenderer/Camera.h>

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
    m_matrix = glm::transpose(glm::mat4(-m_right.x, m_up.x, m_front.x, m_position.x,
                                        -m_right.y, m_up.y, m_front.y, m_position.y,
                                        -m_right.z, m_up.z, m_front.z, m_position.z,
                                         0, 0, 0, 1));

    glm::mat4 tmp = glm::transpose(glm::mat4(1, 0, 0, -0.1f,
        0, 1, 0, -0.2f,
        0, 0, 1, 0,
        0, 0, 0, 1));

    m_matrix *= tmp;

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
