#pragma once

#include <vector>

#include <glm/ext.hpp>

#include <Physics/Export.h>

namespace Physics
{
    class API_PHYSICS RigidBody
    {
    public:
        RigidBody() = default;
        ~RigidBody() = default;

        glm::vec3& GetPosition() { return m_position; }

    private:
        glm::vec3 m_position;

    };
}

