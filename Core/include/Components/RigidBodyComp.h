#pragma once

#include <Components/Component.h>

namespace Components
{
    class RigidBodyComp : public Component
    {
    public:
        RigidBodyComp() {};//: m_rigidbody(new Core::PhysX::RigidBody) {};
        ~RigidBodyComp() {}; //delete m_rigidbody; };

        //Core::PhysX::RigidBody* m_rigidbody;
    };
}

