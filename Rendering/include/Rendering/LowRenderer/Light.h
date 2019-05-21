#pragma once
#include <Rendering/Export.h>

namespace Rendering::LowRenderer
{
    class API_RENDERING Light
    {
    public:
        Light();
        ~Light();

        bool isDirectionnal;
        float intensity;
        glm::vec3 m_pos;
        glm::vec3 m_color;
    };
}

