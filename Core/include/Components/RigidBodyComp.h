#pragma once

#include <Physics/RigidBody.h>

#include <Components/Component.h>
#include <Components/TransformComp.h>
#include <Core/GameObject.h>
#include <Core/GameObjectManager.h>

namespace Components
{
    class RigidBodyComp : public Component
    {
    public:
		RigidBodyComp(Core::GameObject& p_gameObject, Core::GameObjectManager* p_gameObjectManager) : m_gameObject{ p_gameObject },
			m_gameObjectManager{ p_gameObjectManager }, m_rigidbody{ std::make_unique<Physics::RigidBody>() } 
        {
            m_rigidbody->SetPosition(m_gameObject.GetComponent<TransformComp>()->GetTransform()->GetPosition());
        }

		~RigidBodyComp() = default;

        void Update() override
        {
            m_isColliding = false;
            for (auto& gameObject: m_gameObjectManager->GetGameObjects())
            {
				if (glm::distance(gameObject->GetComponent<TransformComp>()->GetTransform()->GetPosition(),
					m_gameObject.GetComponent<TransformComp>()->GetTransform()->GetPosition()) > 100
					|| gameObject->GetComponent<RigidBodyComp>() == nullptr
					|| m_gameObject == *gameObject
					|| m_isKinematic == true)
					continue;

				gameObject->GetComponent<RigidBodyComp>()->AddForce({ 0, -4, 0 });

                if (m_gameObject.CollidesWith(gameObject))
                {
                    m_isColliding = true;
					glm::vec3 currPos = m_gameObject.GetComponent<TransformComp>()->GetTransform()->GetPosition();

					glm::vec3 collisionDirection = (gameObject->GetComponent<TransformComp>()->GetTransform()->GetPosition() -
						m_gameObject.GetComponent<TransformComp>()->GetTransform()->GetPosition());

					m_velocity = glm::vec3(0, 0, 0);
                }
            }

            if (!m_isColliding)
            {
                if (!m_isKinematic)
                {
                    m_velocity += m_force;
                    m_rigidbody->SetPosition(m_rigidbody->GetPosition() + m_velocity);

                }
                m_gameObject.GetComponent<Components::TransformComp>()->GetTransform()->SetPosition(m_rigidbody->GetPosition());
            }
        }

        void Serialize(XMLElement* p_compSegment, XMLDocument& p_xmlDoc) const noexcept override;
        void Deserialize(XMLElement* p_compSegment) const noexcept override;
        
        const glm::vec3& GetVelocity() { return m_velocity; }
        const glm::vec3& GetForce() { return m_force; }
       
        void SetVelocity(const glm::vec3& p_velocity) { m_velocity = p_velocity; }
        void SetForce(const glm::vec3& p_force) { m_force = p_force; }
		void SetKinematic(bool p_kin) { m_isKinematic = p_kin; }

        void AddForce(const glm::vec3& p_force) { m_force += p_force * 0.001f; };
        void ResetVelocity() { m_velocity = glm::vec3(0, 0, 0); }

        std::unique_ptr<Physics::RigidBody>& GetRigidBody() { return m_rigidbody; }

    private:
        bool m_isKinematic{ false };
        bool m_isColliding{ false };

        glm::vec3 m_velocity{};
		glm::vec3 m_force{};

        Core::GameObject& m_gameObject;
        Core::GameObjectManager* m_gameObjectManager;
        std::unique_ptr<Physics::RigidBody> m_rigidbody;
    };
}

