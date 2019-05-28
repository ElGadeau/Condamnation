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
        GameObject(std::shared_ptr<Rendering::Resources::Mesh> p_mesh, Rendering::Shaders::Shader* p_Shader, const char* p_name);
        ~GameObject();

        //Rendering::Resources::Model* m_model;

        void SetGameObjectMesh(std::shared_ptr<Rendering::Resources::Mesh> p_mesh);
        void SetModelShader(Rendering::Shaders::Shader& p_shader);
        void Update(Rendering::LowRenderer::Camera& cam, std::vector<GameObject>& p_lights);
        void ReloadShader();

        static bool CheckCollision(std::vector<std::shared_ptr<GameObject>>& p_gameObjects);

		const std::string& GetName() const noexcept {	return m_name; }

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
        std::string m_name;
        std::vector<std::shared_ptr<Components::Component>> m_components;
    };
}
