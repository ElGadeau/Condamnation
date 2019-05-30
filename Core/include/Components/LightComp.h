#pragma once

#include <Rendering/LowRenderer/Light.h>

#include <Components/Component.h>

namespace Components
{
    class LightComp : public Component
    {
    public:
		LightComp(Core::GameObject& p_gameObject) : m_light{ std::make_shared<Rendering::LowRenderer::Light>() }, m_gameObject{ p_gameObject } {};
		~LightComp() = default;

		[[nodiscard]] std::shared_ptr<Rendering::LowRenderer::Light> GetLight() const noexcept { return m_light; }
		void Update() override {}
    private:
		std::shared_ptr<Rendering::LowRenderer::Light> m_light;
		Core::GameObject& m_gameObject;
    };
}
