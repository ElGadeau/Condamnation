#include <Components/TransformComp.h>
#include <iostream>

Components::TransformComp::TransformComp()
{
    m_transform = new Rendering::LowRenderer::Transform;
}
