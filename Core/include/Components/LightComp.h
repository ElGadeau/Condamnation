#pragma once

#include <Components/Component.h>
#include <Rendering/LowRenderer/Light.h>

namespace Components
{
    class LightComp : public Component
    {
    public:
		LightComp() : m_light { std::make_shared<Rendering::LowRenderer::Light>() } {};
		~LightComp() = default;

		[[nodiscard]] std::shared_ptr<Rendering::LowRenderer::Light> GetLight() const noexcept { return m_light; }

    private:
		std::shared_ptr<Rendering::LowRenderer::Light> m_light;
    };
}
