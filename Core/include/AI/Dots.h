#pragma once
#include <glm/glm.hpp>
#include <list>

namespace Core::AI
{
    struct Dots
    {
        float f;
        float g;
        float h;

        glm::vec3 m_position;
        std::list<Dots> m_neighbors;
    };
}
