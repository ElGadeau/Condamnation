#include <Core/GameObjectManager.h>
#include <tinyxml2.h>
#include "Components/LightComp.h"
#include "Components/TransformComp.h"
#include "Components/MaterialComp.h"

static double angle = 0;

Core::GameObjectManager::GameObjectManager()
{
}

Core::GameObjectManager::GameObjectManager(Core::MeshManager& p_modelManager)
{
    std::shared_ptr<Core::GameObject> flatTerrain(new Core::GameObject(p_modelManager.GetMesh(0), p_modelManager.GetShader(0), "Terrain"));
    std::shared_ptr<Core::GameObject> DirLight(new Core::GameObject(p_modelManager.meshes[1], p_modelManager.GetShader(1),"Directionnal"));
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

    OrangeLight->GetComponent<Components::TransformComp>()->m_transform->Translate(glm::vec3(0, 10, 0));
    OrangeLight->AddComponent<Components::LightComp>()->m_light->m_pos = OrangeLight->GetComponent<Components::TransformComp>()->m_transform->GetPosition();
    OrangeLight->GetComponent<Components::LightComp>()->m_light->m_color = glm::vec3(0, 1, 1);

    BlueLight->GetComponent<Components::TransformComp>()->m_transform->Translate(glm::vec3(0, 10, 0));
    BlueLight->AddComponent<Components::LightComp>()->m_light->m_pos = BlueLight->GetComponent<Components::TransformComp>()->m_transform->GetPosition();
    BlueLight->GetComponent<Components::LightComp>()->m_light->m_color = glm::vec3(1, 0, 1);

    DirLight->GetComponent<Components::TransformComp>()->m_transform->Translate(glm::vec3(0, 20, 20));
    DirLight->AddComponent<Components::LightComp>()->m_light->m_pos = DirLight->GetComponent<Components::TransformComp>()->m_transform->GetPosition();
    DirLight->GetComponent<Components::LightComp>()->m_light->m_color = glm::vec3(0.9, 0.9, 0.9);
    DirLight->GetComponent<Components::LightComp>()->m_light->isDirectionnal = true;
    DirLight->GetComponent<Components::LightComp>()->m_light->intensity = 0.2f;

    flatTerrain->GetComponent<Components::TransformComp>()->m_transform->Rotate(glm::vec3(0, 0, 0));
    flatTerrain->GetComponent<Components::MaterialComp>()->m_material->SetColor(0.8f, 0.8f, 0.8f);

    Gear->GetComponent<Components::TransformComp>()->m_transform->Translate({ 0, 5, 0 });
    Torus->GetComponent<Components::TransformComp>()->m_transform->Translate({ 0, 5, 0 });
    Torus->GetComponent<Components::MaterialComp>()->m_material->SetColor(0, 1, 1);
    Torus->GetComponent<Components::MaterialComp>()->m_material->SetShininess(1);
    Gear->GetComponent<Components::MaterialComp>()->m_material->SetColor(0.4f, 0.4f, 0.4f);
    Gear->GetComponent<Components::MaterialComp>()->m_material->SetShininess(1);
}


Core::GameObjectManager::~GameObjectManager()
{
}

void Core::GameObjectManager::Update(float p_deltaTime)
{
    angle += 0.005f * p_deltaTime;
    Find("OrangeLight")->GetComponent<Components::LightComp>()->m_light->m_pos = Find("OrangeLight")->GetComponent<Components::TransformComp>()->m_transform->GetPosition();
    Find("BlueLight")->GetComponent<Components::TransformComp>()->m_transform->Translate(glm::vec3(cos(angle * 20), 0, sin(angle * 20)) * p_deltaTime);
    Find("BlueLight")->GetComponent<Components::LightComp>()->m_light->m_pos = Find("BlueLight")->GetComponent<Components::TransformComp>()->m_transform->GetPosition();


    Find("Torus")->GetComponent<Components::TransformComp>()->m_transform->Rotate(glm::vec3(1, 0, 0) * p_deltaTime);
    Find("Gear")->GetComponent<Components::TransformComp>()->m_transform->Rotate(glm::vec3(0, 1, 0) * p_deltaTime);
}

int Core::GameObjectManager::LoadScene()
{
    using namespace tinyxml2;

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { std::cout << ("Error: %i\n", a_eResult) << '\n'; return a_eResult; }
#endif

    XMLDocument xmlDoc;
    XMLError eResult = xmlDoc.LoadFile("scene.xml");
    XMLCheckResult(eResult);

    XMLNode* root = xmlDoc.FirstChild();
    if (root == nullptr) return XML_ERROR_FILE_READ_ERROR;

    XMLElement* GOList = root->FirstChildElement("GameObjectList");
    if (GOList == nullptr) return XML_ERROR_PARSING_ELEMENT;

    XMLElement* GOelement = GOList->FirstChildElement("GameObject");
    while (GOelement != nullptr)
    {
        //unordored map -> pointeur sur fonction
        GOelement = GOelement->NextSiblingElement("GameObject");
    }

    return EXIT_SUCCESS;
}

std::shared_ptr<Core::GameObject> Core::GameObjectManager::Find(const std::string & p_name)
{
    for (auto& m_gameObject : m_gameObjects)
    {
        if (m_gameObject->GetName() == p_name)
            return m_gameObject;
    }

    return nullptr;
}
