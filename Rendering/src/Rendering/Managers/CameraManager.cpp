#include "stdafx.h"
#include <Rendering/Managers/CameraManager.h>

Rendering::Managers::CameraManager::CameraManager(glm::vec3 p_position,
    glm::vec3 p_up, float p_yaw, float p_pitch)
{
    Init(p_position, p_up, p_yaw, p_pitch);
}

Rendering::Managers::CameraManager::CameraManager(float p_posX, float p_posY,
    float p_posZ, float p_upX, float p_upY, float p_upZ, float p_yaw, float p_pitch)
{
    Init(glm::vec3(p_posX, p_posY, p_posZ),
        glm::vec3(p_upX, p_upY, p_upZ),
        p_yaw, p_pitch);
}

void Rendering::Managers::CameraManager::Init(glm::vec3 p_position, glm::vec3 p_up,
    float p_yaw, float p_pitch)
{
    m_camera = std::make_shared<Rendering::LowRenderer::Camera>(p_position, p_up, p_yaw, p_pitch);
}

void Rendering::Managers::CameraManager::ProcessKeyInput(std::list<int> p_inputList, const float p_deltaTime)
{
    glm::vec3 nextMove;
    for (auto& input : p_inputList)
    {
        if (input == 87) //move forward
        {
            MoveCamera(m_camera->m_front * p_deltaTime);
        }
        if (input == 65) //move left
        {
            MoveCamera(-m_camera->m_right * p_deltaTime);
        }
        if (input == 83) //move backward
        {
            MoveCamera(-m_camera->m_front * p_deltaTime);
        }
        if (input == 68) //move right
        {
            MoveCamera(m_camera->m_right * p_deltaTime);
        }
        if (input == 340) //move up
        {
            MoveCamera(m_camera->m_up * p_deltaTime);
        }
        if (input == 341) //move down
        {
            MoveCamera(-m_camera->m_up * p_deltaTime);
        }
    }
}

void Rendering::Managers::CameraManager::ProcessMouseInput(glm::vec2 p_inputList)
{
    float Xoffset = p_inputList.x - m_lastX;
    float Yoffset = m_lastY - p_inputList.y;

    Xoffset *= m_camera->m_mouseSensitivity;
    Yoffset *= m_camera->m_mouseSensitivity;

    m_camera->m_yaw += Xoffset;
    m_camera->m_pitch += Yoffset;

    if (m_camera->m_pitch > 89.0f)
        m_camera->m_pitch = 89.0f;
    if (m_camera->m_pitch < -89.0f)
        m_camera->m_pitch = -89.0f;

    // Update Front, Right and Up Vectors using the updated Euler angles
    m_camera->UpdateCameraVectors();
}

void Rendering::Managers::CameraManager::MoveCamera(glm::vec3 p_direction)
{
    m_camera->m_position += p_direction;
}

std::shared_ptr<Rendering::LowRenderer::Camera> Rendering::Managers::CameraManager::GetCamera()
{
    return m_camera;
}
