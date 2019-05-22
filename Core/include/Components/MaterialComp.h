#pragma once
#include <Rendering/LowRenderer/Material.h>
#include <Components/Component.h>

namespace Components
{
    class MaterialComp : public Component
    {
    public:
        MaterialComp() { m_material = new Rendering::LowRenderer::Material; };
        ~MaterialComp() { delete m_material; };

        Rendering::LowRenderer::Material* m_material;
    };
}

