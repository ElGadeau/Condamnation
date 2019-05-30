#pragma once

#include <memory>
#include <Rendering/LowRenderer/Transform.h>
#include <Components/Component.h>
#include <Components/LightComp.h>

namespace Components
{
	class TransformComp : public Component
	{
	public:
		TransformComp(Core::GameObject& p_gameObject) : m_transform{ std::make_shared<Rendering::LowRenderer::Transform>() }, m_gameObject{ p_gameObject },
			m_localTransform{ std::make_shared<Rendering::LowRenderer::Transform>() } {}
		~TransformComp() = default;

		[[nodiscard]] std::shared_ptr<Rendering::LowRenderer::Transform> GetTransform() const noexcept { return m_transform; }
		void SetLocalTransformPos(const glm::vec3& p_pos) { m_localTransform->SetPosition(p_pos); }
		void SetChild(std::shared_ptr<TransformComp> p_child) { m_child = p_child; }
		void SetChild(Core::GameObject& p_child) { m_child = std::shared_ptr<TransformComp>(p_child.GetComponent<TransformComp>()); }
		void SetChild(std::shared_ptr<Core::GameObject> p_child) { m_child = std::shared_ptr<TransformComp>(p_child->GetComponent<TransformComp>()); }
		void SetParent(std::shared_ptr<TransformComp> p_parent) { m_parent = p_parent; }
		void SetParent(Core::GameObject& p_parent) { m_parent = std::shared_ptr<TransformComp>(p_parent.GetComponent<TransformComp>()); }
		void SetParent(std::shared_ptr<Core::GameObject> p_parent) { m_parent = std::shared_ptr<TransformComp>(p_parent->GetComponent<TransformComp>()); }

		void Update()
		{
			if (m_parent != nullptr)
			{
				//m_transform->SetPosition(m_globalTransform->GetPosition() + m_parent->GetTransform()->GetPosition());
				m_transform->SetPosition(m_parent->GetTransform()->GetPosition() + m_localTransform->GetPosition());
				//m_transform->Rotate(m_transform->GetRotation());
				if (m_gameObject.GetComponent<Components::LightComp>() != nullptr)
				{
					//m_gameObject.GetComponent<Components::LightComp>()->GetLight()->m_pos = m_transform->GetPosition();
				}
			}
		}

    private:
		Core::GameObject& m_gameObject;
		std::shared_ptr<TransformComp> m_parent = nullptr;
		std::shared_ptr<TransformComp> m_child = nullptr;
        std::shared_ptr<Rendering::LowRenderer::Transform> m_transform;
        std::shared_ptr<Rendering::LowRenderer::Transform> m_localTransform;
    };
}

