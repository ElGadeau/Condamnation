#include <Core/GameObjectManager.h>
#include <tinyxml2.h>
#include "Components/LightComp.h"
#include "Components/TransformComp.h"
#include "Components/MaterialComp.h"
#include "Components/BoxColliderComp.h"

static double angle = 0;

Core::GameObjectManager::GameObjectManager(Core::MeshManager& p_modelManager)
{
    std::shared_ptr<Core::GameObject> flatTerrain = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(0), p_modelManager.GetShader(0), "Terrain");
    std::shared_ptr<Core::GameObject> DirLight = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1),"Directionnal");
    std::shared_ptr<Core::GameObject> OrangeLight = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "OrangeLight");
    std::shared_ptr<Core::GameObject> BlueLight = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "BlueLight");

    std::shared_ptr<Core::GameObject> Torus = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(3), p_modelManager.GetShader(0), "Torus");
    std::shared_ptr<Core::GameObject> Gear = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(4), p_modelManager.GetShader(0), "Gear");

    m_gameObjects.emplace_back(flatTerrain);
    m_gameObjects.emplace_back(DirLight);
    m_gameObjects.emplace_back(OrangeLight);
    m_gameObjects.emplace_back(BlueLight);
    m_gameObjects.emplace_back(Torus);
    m_gameObjects.emplace_back(Gear);

    OrangeLight->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(0, 10, 0));
    OrangeLight->AddComponent<Components::LightComp>()->GetLight()->m_pos = OrangeLight->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition();
    OrangeLight->GetComponent<Components::LightComp>()->GetLight()->m_color = glm::vec3(1, 1, 0);

    BlueLight->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(0, 10, 0));
    BlueLight->AddComponent<Components::LightComp>()->GetLight()->m_pos = BlueLight->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition();
    BlueLight->GetComponent<Components::LightComp>()->GetLight()->m_color = glm::vec3(0, 0, 1);

    DirLight->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(0, 20, 20));
    DirLight->AddComponent<Components::LightComp>()->GetLight()->m_pos = DirLight->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition();
    DirLight->GetComponent<Components::LightComp>()->GetLight()->m_color = glm::vec3(0.9, 0.9, 0.9);
    DirLight->GetComponent<Components::LightComp>()->GetLight()->isDirectionnal = true;
    DirLight->GetComponent<Components::LightComp>()->GetLight()->intensity = 0.2f;

    flatTerrain->GetComponent<Components::TransformComp>()->GetTransform()->Rotate(glm::vec3(0, 0, 0));
    flatTerrain->GetComponent<Components::MaterialComp>()->GetMaterial()->SetColor(0.8f, 0.8f, 0.8f);

    Gear->GetComponent<Components::TransformComp>()->GetTransform()->Translate({ 20, 20, 20 });
    Torus->GetComponent<Components::TransformComp>()->GetTransform()->Translate({ 40, 5, 10 });
    Torus->GetComponent<Components::MaterialComp>()->GetMaterial()->SetColor(0, 1, 1);
    Torus->GetComponent<Components::MaterialComp>()->GetMaterial()->SetShininess(1);
    Gear->GetComponent<Components::MaterialComp>()->GetMaterial()->SetColor(0.4f, 0.4f, 0.4f);
    Gear->GetComponent<Components::MaterialComp>()->GetMaterial()->SetShininess(1);
}

void Core::GameObjectManager::Update(float p_deltaTime)
{
    angle += 0.005f * p_deltaTime;

    Find("OrangeLight")->GetComponent<Components::LightComp>()->GetLight()->m_pos = Find("OrangeLight")->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition();
    Find("BlueLight")->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(cos(angle * 20), 0, sin(angle * 20)) * p_deltaTime);
    Find("BlueLight")->GetComponent<Components::LightComp>()->GetLight()->m_pos = Find("BlueLight")->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition();

    Find("Torus")->GetComponent<Components::TransformComp>()->GetTransform()->Rotate(glm::vec3(1, 0, 0) * p_deltaTime);
    Find("Torus")->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(cos(angle) / 10, 0, 0) * p_deltaTime);
    Find("Gear")->GetComponent<Components::TransformComp>()->GetTransform()->Rotate(glm::vec3(0, 1, 0) * p_deltaTime);
    Find("Torus")->CollidesWith(Find("Gear"));
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

	std::cout << "Could not find object " << p_name << "in Game Manager\n";
    return nullptr;
}

std::vector<std::shared_ptr<Core::GameObject>>& Core::GameObjectManager::GetGameObjects() noexcept
{
	return m_gameObjects;
}
