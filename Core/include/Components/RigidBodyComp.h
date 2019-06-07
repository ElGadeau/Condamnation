#pragma once

#include <Components/Component.h>
#include <Components/TransformComp.h>
#include <Physics/RigidBody.h>
#include <Core/GameObject.h>

namespace Components
{
    class RigidBodyComp : public Component
    {
    public:
        RigidBodyComp(Core::GameObject& p_gameObject) : m_rigidbody(new Physics::RigidBody),  m_gameObject{ p_gameObject }{}
        ~RigidBodyComp() {delete m_rigidbody; }

        virtual void Update() override
        {
            m_gameObject.GetComponent<Components::TransformComp>()->GetTransform()->SetPosition(m_rigidbody->GetPosition());
        }

    private:

        Core::GameObject& m_gameObject;
        Physics::RigidBody* m_rigidbody;
    };
}

