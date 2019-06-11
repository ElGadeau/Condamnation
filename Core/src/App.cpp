#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <Rendering/Context/OpenGL/GLFWDevice.h>
#include <Rendering/Context/OpenGL/GLEWDriver.h>
#include <Rendering/Managers/Renderer.h>
#include <Rendering/Managers/InputManager.h>
#include <Rendering/Managers/CameraManager.h>

#include <Core/GameObject.h>
#include <Core/GameObjectManager.h>
#include <Core/MeshManager.h>
#include <Core/RenderEngine.h>
#include <Components/LightComp.h>
#include <Components/BoxColliderComp.h>
#include "Components/PlayerComp.h"
#include <Utils/Ray.h>
#include <Components/TransformComp.h>
#include <Rendering/Resources/Texture.h>
#include "Components/RigidBodyComp.h"
#include "Components/ModelComp.h"
#include "Components/MaterialComp.h"


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
    srand(time(nullptr));

    auto device = std::make_unique<Rendering::Context::OpenGL::GLFWDevice>();
	std::unique_ptr<Rendering::Managers::Renderer> renderer = std::make_unique<Rendering::Managers::Renderer>();
    renderer->Initialize<Rendering::Context::OpenGL::GLEWDriver>();
    renderer->SetupCulling();

	Rendering::Managers::InputManager::Init(device->GetWindow());
    Rendering::Managers::CameraManager m_camera(glm::vec3(20.0f, 10, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0, 0, true);

    Core::RenderEngine m_renderEngine;
    Core::MeshManager modelManager;
    modelManager.LoadMeshes();
    modelManager.LoadShaders();
        
    Core::GameObjectManager gameobjects(modelManager);
    
    std::vector<Core::GameObject> lights;
    lights = GenerateLights(gameobjects.GetGameObjects());

	Core::GameObject player("Player");
	Core::GameObject tmp(modelManager.GetMesh(1), modelManager.GetShader(0), "tmp");
	tmp.GetComponent<Components::TransformComp>()->GetTransform()->Translate({ -70, 5, 0 });
	tmp.GetComponent<Components::TransformComp>()->GetTransform()->Scale({ 2, 5, 2 });

	player.GetComponent<Components::TransformComp>()->GetTransform()->Translate({ -70, 5, 0 });
	player.AddComponent<Components::RigidBodyComp>(&gameobjects);
	player.AddComponent<Components::BoxColliderComp>()->SetCollider(tmp.GetComponent<Components::ModelComp>()->GetModel()->GetMesh()->m_positions);
	player.AddComponent<Components::PlayerComp>(m_camera.GetCamera(), 100);

	gameobjects.AddGameObject(player);

    float angle = 0;
	Rendering::Managers::InputManager* inputManager = &*Rendering::Managers::InputManager::GetInstance();

    while (!device->ShouldClose())
    {
        device->CalculateDeltaTime();
        device->RefreshEvents();
		//Utils::RayCast(gameobjects.Find("Player"), m_camera.GetCamera()->GetFront(), gameobjects);
        angle += 0.005f;
        if (inputManager->GetKeyDown(Rendering::Managers::InputManager::KeyCode::R))
            modelManager.ReloadShader(gameobjects.GetGameObjects());

        if (inputManager->GetKeyDown(Rendering::Managers::InputManager::KeyCode::Escape))
            device->Close();

        inputManager->UpdateCursorPos();
        m_camera.ProcessKeyInput(device->GetDeltaTime());
        m_camera.ProcessMouseInput();
        gameobjects.Find("Gun")->GetComponent<Components::TransformComp>()->GetTransform()->SetTransMat(m_camera.GetCamera()->GetMatrix());
		player.GetComponent<Components::PlayerComp>()->ProcessKeyInput(gameobjects, device->GetDeltaTime());
        renderer->Clear();  
        gameobjects.Update(device->GetDeltaTime());
                
        m_renderEngine.DrawElements(gameobjects.GetGameObjects(), lights, *m_camera.GetCamera(), *renderer);
        device->Render();
    }

    return  0;
}

