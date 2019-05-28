#pragma once
#include <Rendering/Export.h>
#include <glm/gtc/matrix_transform.hpp>

namespace Rendering::LowRenderer
{
    class API_RENDERING Camera
    {
    public:
        enum Camera_Movement
        {
            FORWRARD,
            BACKWARD,
            LEFT,
            RIGHT
        };

        //camera attriutes
        glm::vec<3, double> m_position;
        glm::vec<3, double> m_front;
        glm::vec<3, double> m_up;
        glm::vec<3, double> m_right;
        glm::vec<3, double> m_worldUp;

        //euler angles
        double m_yaw   = -90;
        double m_pitch = 0.0f;

        //camera option
        float m_movementSpeed    = 0.5f;
        float m_mouseSensitivity = 0.05f;
        float m_zoom             = 45.0f;

        //constructor with vector
        Camera(const glm::vec3& p_position = glm::vec3(0.0f, 0.0f, 0.0f),
               const glm::vec3& p_up       = glm::vec3(0.0f, 1.0f, 0.0f),
               const float&     p_yaw      = -90.0f,
               const float&     p_pitch    = 0.0f);
        Camera(const float& p_posX, const float& p_posY, const float& p_posZ, const float& p_upX,
               const float& p_upY, const float&  p_upZ, const float&  p_yaw, const float&  p_pitch);
		
        glm::mat4 GetViewMatrix() const noexcept { return lookAt(m_position, m_position + m_front, m_up); };
        static glm::mat4 GetPerspectiveMatrix() noexcept { return glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 1000000.0f); };
		
        void UpdateCameraVectors();
    };
}
