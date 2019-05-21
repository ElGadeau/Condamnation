#pragma once
#include <memory>

#include <Rendering/Export.h>
#include <Rendering/LowRenderer/Camera.h>
#include <list>
#include "InputManager.h"

namespace Rendering::Managers
{
    class API_RENDERING CameraManager
    {
    public:
        CameraManager(glm::vec3 p_position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 p_up = glm::vec3(0.0f, 1.0f, 0.0f), float p_yaw = LowRenderer::YAW, float p_pitch = LowRenderer::PITCH);
        CameraManager(float p_posX, float p_posY, float p_posZ, float p_upX, float p_upY, float p_upZ, float p_yaw, float p_pitch);

        void Init(glm::vec3 p_position, glm::vec3 p_up, float p_yaw, float p_pitch);

        void ProcessKeyInput(InputManager& p_inputManager, const float p_deltaTime);
        void ProcessMouseInput(const std::tuple<double, double>& p_mouseCursor);
        void MoveCamera(glm::vec3 p_direction);

        std::shared_ptr<LowRenderer::Camera> GetCamera();

    private:
        std::shared_ptr<LowRenderer::Camera> m_camera;

        float m_lastX = 1920 / 2;
        float m_lastY = 1080 / 2;
    };
}
