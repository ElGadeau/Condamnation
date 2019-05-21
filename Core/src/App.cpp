#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <math.h>

#include <Core/GameObject.h>
#include <Core/MeshManager.h>

#include <Components/include/Component.h>
#include <Components/include/TransformComp.h>
#include <Components/include/LightComp.h>
#include <Components/include/RigidBodyComp.h>

#include <Rendering/Context/OpenGL/GLFWDevice.h>
#include <Rendering/Context/OpenGL/GLEWDriver.h>

#include <Rendering/Managers/Renderer.h>
#include <Rendering/Managers/InputManager.h>
#include <Rendering/Managers/CameraManager.h>

#include <Rendering/Resources/Mesh.h>
#include "Core/RenderEngine.h"

std::vector<Core::GameObject> GenerateLights(std::vector<std::shared_ptr<Core::GameObject>>& m_gameObjectVector)
{
    std::vector<Core::GameObject> m_lights;
    for (auto p_light : m_gameObjectVector)
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

    auto inputManager = std::make_unique<Rendering::Managers::InputManager>(device->GetWindow());

    std::vector<std::shared_ptr<Core::GameObject>> gameObjectVector;
    std::vector<std::shared_ptr<Core::GameObject>> rigidBodies;
    std::vector<Core::GameObject> lights;

    Rendering::Managers::InputManager m_inputManager(device->GetWindow());
    Core::RenderEngine m_renderEngine;
    Core::MeshManager m_modelManager;
    Rendering::Managers::CameraManager m_camera(glm::vec3(20.0f, 0, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, -25.0f);

    m_modelManager.AddMesh(R"(..\Resources\Meshes\plane2.obj)");
    m_modelManager.AddMesh(R"(..\Resources\Meshes\sphere.fbx)");
    m_modelManager.AddMesh(R"(..\Resources\Meshes\plane.fbx)");
    m_modelManager.AddMesh(R"(..\Resources\Meshes\torus.fbx)");
    m_modelManager.AddMesh(R"(..\Resources\Meshes\gear.fbx)");

    m_modelManager.AddShader("../Resources/Shaders/vertShader.vert", "../Resources/Shaders/fragShader2.frag");
    m_modelManager.AddShader("../Resources/Shaders/vertShader.vert", "../Resources/Shaders/lightShader.frag");

    std::shared_ptr<Core::GameObject> flatTerrain(new Core::GameObject(m_modelManager.GetMesh(0), m_modelManager.GetShader(0)));
    std::shared_ptr<Core::GameObject> DirLight(new Core::GameObject(m_modelManager.GetMesh(1), m_modelManager.GetShader(1)));
    std::shared_ptr<Core::GameObject> OrangeLight(new Core::GameObject(m_modelManager.GetMesh(1), m_modelManager.GetShader(1)));
    std::shared_ptr<Core::GameObject> BlueLight(new Core::GameObject(m_modelManager.GetMesh(1), m_modelManager.GetShader(1)));
    std::shared_ptr<Core::GameObject> Torus(new Core::GameObject(m_modelManager.GetMesh(3), m_modelManager.GetShader(0)));
    std::shared_ptr<Core::GameObject> Gear(new Core::GameObject(m_modelManager.GetMesh(4), m_modelManager.GetShader(0)));

    gameObjectVector.emplace_back(flatTerrain);
    gameObjectVector.emplace_back(DirLight);
    gameObjectVector.emplace_back(OrangeLight);
    gameObjectVector.emplace_back(BlueLight);
    gameObjectVector.emplace_back(Torus);
    gameObjectVector.emplace_back(Gear);


    OrangeLight->GetComponent<Components::TransformComp>()->m_transform->Translate(glm::vec3(0, 60, 0));
    OrangeLight->AddComponent<Components::LightComp>()->m_light->m_pos = OrangeLight->GetComponent<Components::TransformComp>()->m_transform->GetPosition();
    OrangeLight->GetComponent<Components::LightComp>()->m_light->m_color = glm::vec3(1, 0.647, 0);

    BlueLight->GetComponent<Components::TransformComp>()->m_transform->Translate(glm::vec3(0, 10, 0));
    BlueLight->AddComponent<Components::LightComp>()->m_light->m_pos = BlueLight->GetComponent<Components::TransformComp>()->m_transform->GetPosition();
    BlueLight->GetComponent<Components::LightComp>()->m_light->m_color = glm::vec3(0, 0.745, 1);

    DirLight->GetComponent<Components::TransformComp>()->m_transform->Translate(glm::vec3(0, 20, 20));
    DirLight->AddComponent<Components::LightComp>()->m_light->m_pos = DirLight->GetComponent<Components::TransformComp>()->m_transform->GetPosition();
    DirLight->GetComponent<Components::LightComp>()->m_light->m_color = glm::vec3(0.9, 0.9, 0.6);
    DirLight->GetComponent<Components::LightComp>()->m_light->isDirectionnal = true;
    DirLight->GetComponent<Components::LightComp>()->m_light->intensity = 0.2f;

    flatTerrain->GetComponent<Components::TransformComp>()->m_transform->Rotate(glm::vec3(0, 0, 0));

    Gear->GetComponent<Components::TransformComp>()->m_transform->Translate({ 5, 5, 0 });
    Torus->GetComponent<Components::TransformComp>()->m_transform->Translate({ -5, 5, 1 });


    lights = GenerateLights(gameObjectVector);

    float angle = 0;
    while (!device->ShouldClose())
    {
        angle += 0.005f;
        for (auto& inputKey : m_inputManager.GetKeyInputList())
        {
            if (inputKey == 82)
                m_modelManager.ReloadShader(gameObjectVector);
        }

        device->CalculateDeltaTime();
        device->RefreshEvents();
        renderer->Clear();

        OrangeLight->GetComponent<Components::LightComp>()->m_light->m_pos = OrangeLight->GetComponent<Components::TransformComp>()->m_transform->GetPosition();
        BlueLight->GetComponent<Components::TransformComp>()->m_transform->Translate(glm::vec3(cos(angle) / 10, 0, sin(angle) / 10) * device->GetDeltaTime());
        BlueLight->GetComponent<Components::LightComp>()->m_light->m_pos = BlueLight->GetComponent<Components::TransformComp>()->m_transform->GetPosition();
        
        
        Torus->GetComponent<Components::TransformComp>()->m_transform->Rotate(glm::vec3( 1, 0, 0 ) * device->GetDeltaTime());
        Gear->GetComponent<Components::TransformComp>()->m_transform->Rotate(glm::vec3( 0, 1, 0 ) * device->GetDeltaTime());
        m_camera.ProcessKeyInput(m_inputManager.GetKeyInputList(), device->GetDeltaTime());
        m_camera.ProcessMouseInput(m_inputManager.GetMouseInputList());

        m_renderEngine.DrawElements(gameObjectVector, lights, *m_camera.GetCamera(), *renderer);

        device->Render();

    }

    return  0;
}

