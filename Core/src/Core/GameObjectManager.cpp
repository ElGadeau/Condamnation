#include <Core/GameObjectManager.h>

Core::GameObjectManager::GameObjectManager()
{
}

Core::GameObjectManager::GameObjectManager(Core::MeshManager& p_modelManager)
{
    std::shared_ptr<Core::GameObject> flatTerrain(new Core::GameObject(p_modelManager.GetMesh(0), p_modelManager.GetShader(0), "Terrain"));
    std::shared_ptr<Core::GameObject> DirLight(new Core::GameObject(p_modelManager.GetMesh(1), p_modelManager.GetShader(1),"Directionnal"));
    std::shared_ptr<Core::GameObject> OrangeLight(new Core::GameObject(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "OrangeLight"));
    std::shared_ptr<Core::GameObject> BlueLight(new Core::GameObject(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "BlueLight"));
    std::shared_ptr<Core::GameObject> Torus(new Core::GameObject(p_modelManager.GetMesh(3), p_modelManager.GetShader(0), "Torus"));
    std::shared_ptr<Core::GameObject> Gear(new Core::GameObject(p_modelManager.GetMesh(4), p_modelManager.GetShader(0), "Gear"));

    m_gameObjects.emplace_back(flatTerrain);
    m_gameObjects.emplace_back(DirLight);
    m_gameObjects.emplace_back(OrangeLight);
    m_gameObjects.emplace_back(BlueLight);
    m_gameObjects.emplace_back(Torus);
    m_gameObjects.emplace_back(Gear);

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
}


Core::GameObjectManager::~GameObjectManager()
{
}

void Core::GameObjectManager::Update(float deltaTime)
{
    Find("OrangeLight")->GetComponent<Components::LightComp>()->m_light->m_pos = Find("OrangeLight")->GetComponent<Components::TransformComp>()->m_transform->GetPosition();
    Find("BlueLight")->GetComponent<Components::TransformComp>()->m_transform->Translate(glm::vec3(cos(1) / 10, 0, sin(1) / 10) * deltaTime);
    Find("BlueLight")->GetComponent<Components::LightComp>()->m_light->m_pos = Find("BlueLight")->GetComponent<Components::TransformComp>()->m_transform->GetPosition();


    Find("Torus")->GetComponent<Components::TransformComp>()->m_transform->Rotate(glm::vec3(1, 0, 0) * deltaTime);
    Find("Gear")->GetComponent<Components::TransformComp>()->m_transform->Rotate(glm::vec3(0, 1, 0) *deltaTime);
}

std::shared_ptr<Core::GameObject> Core::GameObjectManager::Find(const std::string & p_name)
{
    for (int i = 0; i < m_gameObjects.size(); ++i)
    {
        if (m_gameObjects[i]->GetName() == p_name)
            return m_gameObjects[i];
    }

    return nullptr;
}
