#pragma once
#include <Components/Component.h>
#include <Physics/BoxCollider.h>
#include <glm/ext.hpp>

namespace Components
{
    class BoxColliderComp : public Component
    {
    public:
        BoxColliderComp() = default;
        ~BoxColliderComp() { delete m_collider; }

        void SetCollider(std::vector<glm::vec3>& p_vec) { m_collider = new Physics::Collider(p_vec); }
        Physics::Collider* m_collider;
    };
}