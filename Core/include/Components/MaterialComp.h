#pragma once
#include <Rendering/LowRenderer/Material.h>
#include <Components/Component.h>

namespace Components
{
    class MaterialComp : public Component
    {
    public:
		MaterialComp() : m_material { std::make_shared<Rendering::LowRenderer::Material>() } {};
		~MaterialComp() = default;

		[[nodiscard]] std::shared_ptr<Rendering::LowRenderer::Material> GetMaterial() const noexcept { return m_material; }

    private:
        std::shared_ptr<Rendering::LowRenderer::Material> m_material;
    };
}

