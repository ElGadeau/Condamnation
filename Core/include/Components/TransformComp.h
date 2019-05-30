#pragma once

#include <memory>
#include <Rendering/LowRenderer/Transform.h>
#include <Components/Component.h>

namespace Components
{
	class TransformComp : public Component
	{
	public:
		TransformComp(Core::GameObject& p_gameObject) : m_transform{ std::make_unique<Rendering::LowRenderer::Transform>() }, m_gameObject{ p_gameObject } {}
		~TransformComp() = default;

		[[nodiscard]] std::shared_ptr<Rendering::LowRenderer::Transform> GetTransform() const noexcept { return m_transform; }

    private:
        std::shared_ptr<Rendering::LowRenderer::Transform> m_transform;
		Core::GameObject& m_gameObject;
    };
}

