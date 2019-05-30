#include "stdafx.h"
#include <Rendering/Managers/CameraManager.h>
#include <Rendering/Managers/InputManager.h>

Rendering::Managers::CameraManager::CameraManager(const glm::vec3& p_position,
    const glm::vec3& p_up, const float& p_yaw, const float& p_pitch, bool p_freeFloat)
{
    Init(p_position, p_up, p_yaw, p_pitch);
	m_freeFloat = p_freeFloat;
}

Rendering::Managers::CameraManager::CameraManager(const float& p_posX, const float& p_posY,
    const float& p_posZ, const float& p_upX, const float& p_upY, const float& p_upZ, const float& p_yaw, const float& p_pitch)
{
    Init(glm::vec3(p_posX, p_posY, p_posZ),
        glm::vec3(p_upX, p_upY, p_upZ),
        p_yaw, p_pitch);
}

void Rendering::Managers::CameraManager::Init(const glm::vec3& p_position, const glm::vec3& p_up,
    const float& p_yaw, const float& p_pitch)
{
    m_camera = std::make_shared<Rendering::LowRenderer::Camera>(p_position, p_up, p_yaw, p_pitch);
}

void Rendering::Managers::CameraManager::ProcessKeyInput(InputManager& p_inputManager, const double& p_deltaTime)
{
	glm::vec3 FPS = m_camera->m_front;
	FPS.y = 0.0f;
	glm::vec3 freeFloat = m_camera->m_front;

    if (p_inputManager.GetKey(InputManager::KeyCode::W)) //move forward
    {
		if (m_freeFloat)
			MoveCamera(freeFloat * static_cast<float>(p_deltaTime));
		else
			MoveCamera(FPS * static_cast<float>(p_deltaTime));
    }
    if (p_inputManager.GetKey(InputManager::KeyCode::A)) //move left
    {
        MoveCamera(-m_camera->m_right * p_deltaTime);
    }
    if (p_inputManager.GetKey(InputManager::KeyCode::S)) //move backward
    {
		if (m_freeFloat)
			MoveCamera(-freeFloat * static_cast<float>(p_deltaTime));
		else
			MoveCamera(-FPS * static_cast<float>(p_deltaTime));
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
    double Xoffset = std::get<0>(p_mouseCursor) - m_lastX;
    double Yoffset = m_lastY - std::get<1>(p_mouseCursor);

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

void Rendering::Managers::CameraManager::MoveCamera(const glm::vec3& p_direction)
{
    m_camera->m_position += p_direction * m_camera->m_movementSpeed;
}
