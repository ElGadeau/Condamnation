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
		RigidBodyComp(Core::GameObject& p_gameObject, Core::GameObjectManager* p_gameObjectManager) : m_gameObject{ p_gameObject },
			m_gameObjectManager{ p_gameObjectManager }, m_rigidbody{ std::make_unique<Physics::RigidBody>() } {}
		virtual ~RigidBodyComp() = default;

		void SetKinematic(bool p_kin) { m_isKinematic = p_kin; }
        void Update() override
        {
			
			m_gameObject.GetComponent<Components::TransformComp>()->GetTransform()->SetPosition(m_rigidbody->GetPosition());
			m_velocity += m_force;
			m_rigidbody->SetPosition(m_rigidbody->GetPosition() + m_velocity);
			m_gameObject.GetComponent<Components::TransformComp>()->GetTransform()->SetPosition(m_rigidbody->GetPosition());
			//m_rigidbody->SetPosition(m_gameObject.GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());

            for (auto& gameObject: m_gameObjectManager->GetGameObjects())
            {
				if (glm::distance(gameObject->GetComponent<TransformComp>()->GetTransform()->GetPosition(),
					m_gameObject.GetComponent<TransformComp>()->GetTransform()->GetPosition()) > 100
					|| gameObject->GetComponent<RigidBodyComp>() == nullptr
					|| m_gameObject == *gameObject
					|| m_isKinematic == true)
					continue;

                if (m_gameObject.CollidesWith(gameObject))
                {
					glm::vec3 currPos = m_gameObject.GetComponent<TransformComp>()->GetTransform()->GetPosition();

					glm::vec3 collisionDirection = (gameObject->GetComponent<TransformComp>()->GetTransform()->GetPosition() -
						m_gameObject.GetComponent<TransformComp>()->GetTransform()->GetPosition());

					//collisionDirection *= 3;
					m_velocity = glm::vec3(0, 0, 0);
					//m_gameObject.GetComponent<TransformComp>()->GetTransform()->SetPosition(glm::normalize(-m_deltaPos));
                }
            }

			//m_deltaPos = m_gameObject.GetComponent<TransformComp>()->GetTransform()->GetPosition() - m_deltaPos;
        }

		void Serialize(XMLElement* p_compSegment, XMLDocument& p_xmlDoc) const noexcept override {}
		void Deserialize(XMLElement* p_compSegment) const noexcept override {}

    public:
		bool m_isKinematic = false;
		//glm::vec3 m_deltaPos;
		glm::vec3 m_velocity;
		glm::vec3 m_force{ 0, -0.001f, 0 };

        Core::GameObject& m_gameObject;
        Core::GameObjectManager* m_gameObjectManager;
        std::unique_ptr<Physics::RigidBody> m_rigidbody;
    };
}

