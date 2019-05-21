#pragma once

#include <Rendering/LowRenderer/Transform.h>
#include <Components/include/Component.h>

namespace Components
{
    class TransformComp : public Component
    {
    public:
        TransformComp();
        ~TransformComp() { m_transform; };
        Rendering::LowRenderer::Transform* m_transform;
    };
}

