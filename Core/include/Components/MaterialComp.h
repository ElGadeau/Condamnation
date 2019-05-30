#pragma once

#include <Rendering/LowRenderer/Material.h>

#include <Components/Component.h>

namespace Components
{
    class MaterialComp : public Component
    {
    public:
		MaterialComp(Core::GameObject& p_gameObject) : m_material{ std::make_shared<Rendering::LowRenderer::Material>() }, m_gameObject{ p_gameObject } {};
		~MaterialComp() = default;

		[[nodiscard]] std::shared_ptr<Rendering::LowRenderer::Material> GetMaterial() const noexcept { return m_material; }
		void Update() override {}
    private:
        std::shared_ptr<Rendering::LowRenderer::Material> m_material;
		Core::GameObject& m_gameObject;
    };
}

