#pragma once
#include <Components/include/Component.h>
#include <PhysX/RigidBody.h>

namespace Components
{
    class RigidBodyComp : public Component
    {
    public:
        RigidBodyComp() : m_rigidbody(new Core::PhysX::RigidBody) {};
        ~RigidBodyComp() { delete m_rigidbody; };

        Core::PhysX::RigidBody* m_rigidbody;
    };
}

