#pragma once

#include <Components/include/Component.h>
#include <Rendering/LowRenderer/Light.h>

namespace Components
{
    class LightComp : public Component
    {
    public:
        LightComp() : m_light(new Rendering::LowRenderer::Light) {};
        ~LightComp() { delete m_light; };

        Rendering::LowRenderer::Light* m_light;
    };
}
