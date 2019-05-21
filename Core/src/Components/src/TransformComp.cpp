#include <Components/include/TransformComp.h>
#include <iostream>

Components::TransformComp::TransformComp()
{
    m_transform = new Rendering::LowRenderer::Transform;
}
