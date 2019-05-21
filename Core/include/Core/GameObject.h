#pragma once
#include <iostream>
#include <any>
#include <string>
#include <Rendering/Export.h>
#include <Rendering/Resources/Model.h>
#include <Rendering/LowRenderer/Transform.h>
#include <Rendering/LowRenderer/Camera.h>
#include <Components/include/Component.h>

namespace Core
{
    class GameObject
    {
    public:
        GameObject();
        GameObject(const std::string& p_meshPath, const std::string& p_vertPath, const std::string& p_fragPath);
        GameObject(std::shared_ptr<Rendering::Resources::Mesh> p_mesh, Rendering::Shaders::Shader* p_Shader);
        ~GameObject();

        Rendering::Resources::Model* m_model;

        void SetGameObjectMesh(std::shared_ptr<Rendering::Resources::Mesh> p_mesh);
        void SetModelShader(Rendering::Shaders::Shader& p_shader);
        void Update(Rendering::LowRenderer::Camera& cam, std::vector<GameObject>& p_lights);
        void ReloadShader();

        template<class ComponentType>
        ComponentType* AddComponent()
        {
            std::shared_ptr<ComponentType> comp = std::make_shared<ComponentType>();
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
                //std::cout << "Component not found !" << std::endl;
            }
            
            return result.get();
        }

    private:
        std::vector<std::shared_ptr<Components::Component>> m_components;
    };
}
