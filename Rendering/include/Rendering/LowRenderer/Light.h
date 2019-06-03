#pragma once

#include <Rendering/Export.h>

namespace Rendering::LowRenderer
{
    class API_RENDERING Light
    {
    public:
        Light();
        ~Light() = default;

        bool isDirectionnal = false;
        float intensity = 0.0f;
        glm::vec3 m_pos{};
        glm::vec3 m_color{};
    };
}

