#pragma once

#include <memory>
#include <Rendering/LowRenderer/Transform.h>
#include <Components/Component.h>

namespace Components
{
	class TransformComp : public Component
	{
	public:
		TransformComp() : m_transform { std::make_unique<Rendering::LowRenderer::Transform>() } {}
		~TransformComp() = default;

		[[nodiscard]] std::shared_ptr<Rendering::LowRenderer::Transform> GetTransform() const noexcept { return m_transform; }

    private:
        std::shared_ptr<Rendering::LowRenderer::Transform> m_transform;
    };
}

