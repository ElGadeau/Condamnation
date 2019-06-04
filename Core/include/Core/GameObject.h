#pragma once

#include <iostream>
#include <string>

#include <Rendering/Resources/Model.h>
#include <Rendering/LowRenderer/Camera.h>

#include <Components/Component.h>

namespace Core
{
    class GameObject
    {
    public:
        GameObject();
        GameObject(const char* p_name);
        GameObject(const std::shared_ptr<Rendering::Resources::Mesh>& p_mesh, const std::shared_ptr<Rendering::Shaders::Shader>& p_shader, const char* p_name);
        ~GameObject() = default;

        void SetGameObjectMesh(std::shared_ptr<Rendering::Resources::Mesh>& p_mesh);
        void SetModelShader(std::shared_ptr<Rendering::Shaders::Shader>& p_shader);

        void Update(Rendering::LowRenderer::Camera& cam, std::vector<GameObject>& p_lights);
        void ReloadShader();

        bool CollidesWith(const std::shared_ptr<GameObject>& p_gameObjects);
        void ResolveCollisions(std::vector<std::shared_ptr<Core::GameObject>>& p_gameObjects);
		const std::string& GetName() const noexcept { return m_name; }

        template<class ComponentType, typename ... args>
        ComponentType* AddComponent(args ... p_args)
        {
            std::shared_ptr<ComponentType> comp = std::make_shared<ComponentType>(*this, p_args ...);
            m_components.emplace_back(comp);
            return comp.get();
        }

        template<class ComponentType>
        ComponentType* GetComponent() const noexcept
        {
            std::shared_ptr<ComponentType> result;

            if (m_components.empty())
                return nullptr;

            for (auto& component : m_components)
            {
                assert(component != nullptr);
                if (result = std::dynamic_pointer_cast<ComponentType>(component))
                {
                    break;
                }
            }
            if (result == nullptr)
            {
                return nullptr;
            }

            return result.get();
        }

    private:
        float degree{0.0f};
        std::string m_name{};
		std::shared_ptr<GameObject> m_parent = nullptr;
		std::shared_ptr<GameObject> m_child = nullptr;
        std::vector<std::shared_ptr<Components::Component>> m_components{};
    };

	bool operator==(GameObject& p_1, GameObject& p_2);
}
