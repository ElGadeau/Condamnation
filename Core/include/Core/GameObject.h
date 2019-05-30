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
        GameObject(const char* p_meshPath, const char* p_vertPath, const char* p_fragPath);
        GameObject(std::shared_ptr<Rendering::Resources::Mesh> p_mesh, std::shared_ptr<Rendering::Shaders::Shader> p_Shader, const char* p_name);
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
        ComponentType* GetComponent()
        {
           std::shared_ptr<ComponentType> result;

            for (auto& component : m_components) 
            {
                if (result = std::dynamic_pointer_cast<ComponentType>(component))
                {
                    break;
                }
            }
            if(result == nullptr)
            {
                std::cout << "Component not found !" << std::endl;
            }
            
            return result.get();
        }

    private:
        float degree;
        std::string m_name;
		std::shared_ptr<GameObject> m_parent = nullptr;
		std::shared_ptr<GameObject> m_child = nullptr;
        std::vector<std::shared_ptr<Components::Component>> m_components;
    };
}
