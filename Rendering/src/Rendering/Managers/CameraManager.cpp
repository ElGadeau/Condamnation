#include "stdafx.h"
#include <Rendering/Managers/CameraManager.h>
#include <Rendering/Managers/InputManager.h>

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

void Rendering::Managers::CameraManager::ProcessKeyInput(InputManager& p_inputManager, const float p_deltaTime)
{
    glm::vec3 nextMove;
    if (p_inputManager.GetKey(InputManager::KeyCode::W)) //move forward
    {
        MoveCamera(m_camera->m_front * p_deltaTime);
    }
    if (p_inputManager.GetKey(InputManager::KeyCode::A)) //move left
    {
        MoveCamera(-m_camera->m_right * p_deltaTime);
    }
    if (p_inputManager.GetKey(InputManager::KeyCode::S)) //move backward
    {
        MoveCamera(-m_camera->m_front * p_deltaTime);
    }
    if (p_inputManager.GetKey(InputManager::KeyCode::D)) //move right
    {
        MoveCamera(m_camera->m_right * p_deltaTime);
    }
    if (p_inputManager.GetKey(InputManager::KeyCode::LeftShift)) //move up
    {
        MoveCamera(m_camera->m_worldUp * p_deltaTime);
    }
    if (p_inputManager.GetKey(InputManager::KeyCode::LeftControl)) //move down
    {
        MoveCamera(-m_camera->m_worldUp * p_deltaTime);
    }
}

void Rendering::Managers::CameraManager::ProcessMouseInput(const std::tuple<double, double>& p_mouseCursor)
{
    float Xoffset = std::get<0>(p_mouseCursor) - m_lastX;
    float Yoffset = m_lastY - std::get<1>(p_mouseCursor);

    m_lastX = std::get<0>(p_mouseCursor);
    m_lastY = std::get<1>(p_mouseCursor);

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
    m_camera->m_position += p_direction * m_camera->m_movementSpeed;
}

std::shared_ptr<Rendering::LowRenderer::Camera> Rendering::Managers::CameraManager::GetCamera()
{
    return m_camera;
}
