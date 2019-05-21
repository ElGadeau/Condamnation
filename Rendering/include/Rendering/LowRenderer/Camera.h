#pragma once
#include <Rendering/Export.h>

namespace Rendering::LowRenderer
{
    enum Camera_Movement
    {
        FORWRARD,
        BACKWARD,
        LEFT,
        RIGHT
    };

    //default camera value
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float SPEED = 0.5f;
    const float SENSITIVITY = 0.05f;
    const float ZOOM = 45.0f;

    class API_RENDERING Camera
    {
    public:
        //camera attriutes
        glm::vec3 m_position;
        glm::vec3 m_front;
        glm::vec3 m_up;
        glm::vec3 m_right;
        glm::vec3 m_worldUp;

        //euler angles
        float m_yaw;
        float m_pitch;

        //camera option
        float m_movementSpeed;
        float m_mouseSensitivity;
        float m_zoom;

        //constructor with vector
        Camera(glm::vec3 p_position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 p_up = glm::vec3(0.0f, 1.0f, 0.0f), float p_yaw = YAW, float p_pitch = PITCH);
        Camera(float p_posX, float p_posY, float p_posZ, float p_upX, float p_upY, float p_upZ, float p_yaw, float p_pitch);

        glm::mat4 GetViewMatrix();
        glm::mat4 GetPerspectiveMatrix();

        void UpdateCameraVectors();
    };
}