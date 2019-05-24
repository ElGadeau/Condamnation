#pragma once
#include <Components/Component.h>
#include <Physics/BoxCollider.h>

namespace Components
{
    class BoxColliderComp : public Component
    {
    public:
        BoxColliderComp() : m_collider(new Physics::Collider) {}
        ~BoxColliderComp() { delete m_collider; }

        Physics::Collider* m_collider;
    };
}