#pragma once
#include <Core/GameObject.h>
#include <Rendering/Managers/Renderer.h>

namespace Core
{
    class RenderEngine
    {
    public:
        void DrawElements(std::vector<std::shared_ptr<Core::GameObject>>& p_gameObject, std::vector<GameObject>& p_lights,
            Rendering::LowRenderer::Camera& p_camera, Rendering::Managers::Renderer& p_renderer);
    };
}
