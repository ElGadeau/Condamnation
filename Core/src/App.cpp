#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>

#include <Core/GameObject.h>
#include <Core/GameObjectManager.h>
#include <Core/MeshManager.h>

#include <Components/Component.h>
#include <Components/TransformComp.h>
#include <Components/LightComp.h>

#include <Rendering/Context/OpenGL/GLFWDevice.h>
#include <Rendering/Context/OpenGL/GLEWDriver.h>

#include <Rendering/Managers/Renderer.h>
#include <Rendering/Managers/InputManager.h>
#include <Rendering/Managers/CameraManager.h>

#include <Physics/Physics.h>

#include <Rendering/Resources/Mesh.h>
#include <Core/RenderEngine.h>

std::vector<Core::GameObject> GenerateLights(std::vector<std::shared_ptr<Core::GameObject>>& m_gameObjectVector)
{
    std::vector<Core::GameObject> m_lights;
    for (auto& p_light : m_gameObjectVector)
    {
        if (p_light->GetComponent<Components::LightComp>() != nullptr)
        {
            m_lights.emplace_back(*p_light);
        }
    }

    return m_lights;
}

int main()
{
    auto device = std::make_unique<Rendering::Context::OpenGL::GLFWDevice>();
    auto renderer = std::make_unique<Rendering::Managers::Renderer>();
    renderer->Initialize<Rendering::Context::OpenGL::GLEWDriver>();
    renderer->SetupCulling();

    Rendering::Managers::InputManager m_inputManager(device->GetWindow());
    Rendering::Managers::CameraManager m_camera(glm::vec3(20.0f, 0, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -25.0f);
    
    Core::RenderEngine m_renderEngine;
    Core::MeshManager modelManager;
    modelManager.LoadMeshes();
    modelManager.LoadShaders();
    
    Core::GameObjectManager gameobjects(modelManager);
        
    std::vector<Core::GameObject> lights;
    lights = GenerateLights(gameobjects.m_gameObjects);
    
    float angle = 0;
    while (!device->ShouldClose())
    {
        device->CalculateDeltaTime();
        device->RefreshEvents();
        
        angle += 0.005f;
        if (m_inputManager.GetKeyDown(Rendering::Managers::InputManager::KeyCode::R))
            modelManager.ReloadShader(gameobjects.m_gameObjects);

        if (m_inputManager.GetKeyDown(Rendering::Managers::InputManager::KeyCode::Escape))
            device->Close();

        m_inputManager.UpdateCursorPos();
        m_camera.ProcessKeyInput(m_inputManager, device->GetDeltaTime());
        m_camera.ProcessMouseInput(m_inputManager.GetMouseCursorPos());

        renderer->Clear();
        gameobjects.Update(device->GetDeltaTime());
        Core::GameObject::CheckCollision(gameobjects.m_gameObjects);
                
        m_renderEngine.DrawElements(gameobjects.m_gameObjects, lights, *m_camera.GetCamera(), *renderer);
        
        device->Render();

    }

    return  0;
}

