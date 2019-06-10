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
		RigidBody(glm::vec3& p_pos);
        ~RigidBody() = default;

		[[nodiscard]] glm::vec3& GetPosition();

		void SetPosition(const glm::vec3& p_pos);

    private:
        glm::vec3 m_position;

    };
}

