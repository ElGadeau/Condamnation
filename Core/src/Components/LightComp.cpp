#include <Components/LightComp.h>

void Components::LightComp::GenerateLights(std::vector<std::shared_ptr<Core::GameObject>>& m_gameObjects, std::vector<std::shared_ptr<Core::GameObject>>& m_lights)
{
    std::vector<std::shared_ptr<Core::GameObject>> m_lightstmp;
    for (auto p_light : m_gameObjects)
    {
        if (p_light->GetComponent<Components::LightComp>() != nullptr)
        {
            m_lightstmp.emplace_back(p_light);
        }
    }

    m_lights = m_lightstmp;
}
