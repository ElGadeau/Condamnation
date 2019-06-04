#include <tinyxml2.h>

#include <Core/GameObjectManager.h>
#include <Components/LightComp.h>
#include <Components/TransformComp.h>
#include <Components/MaterialComp.h>
#include <Components/BoxColliderComp.h>
#include <Components/ModelComp.h>
#include <unordered_map>

Core::GameObjectManager::GameObjectManager(MeshManager& p_modelManager)
{
    std::shared_ptr<GameObject> flatTerrain = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(0), p_modelManager.GetShader(0), "Terrain");
    std::shared_ptr<GameObject> DirLight = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1),"Directionnal");
    std::shared_ptr<GameObject> OrangeLight = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "OrangeLight");
    std::shared_ptr<GameObject> BlueLight = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "BlueLight");
    std::shared_ptr<GameObject> EmptyGameObject = std::make_shared<Core::GameObject>("Empty");

    std::shared_ptr<GameObject> Torus = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(3), p_modelManager.GetShader(0), "Torus");
    std::shared_ptr<GameObject> Gear = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(0), "Gear");

    m_gameObjects.push_back(flatTerrain);
    m_gameObjects.push_back(DirLight);
    m_gameObjects.push_back(OrangeLight);
    m_gameObjects.push_back(BlueLight);
    m_gameObjects.push_back(Torus);
    m_gameObjects.push_back(Gear);
    m_gameObjects.push_back(EmptyGameObject);

    OrangeLight->GetComponent<Components::TransformComp>()->SetLocalTransformPos(glm::vec3(0, 4, 0));
    OrangeLight->AddComponent<Components::LightComp>()->GetLight()->SetPos(OrangeLight->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
    OrangeLight->GetComponent<Components::LightComp>()->GetLight()->SetColor(0, 1, 1);

    BlueLight->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(0, 2, 0));
    BlueLight->AddComponent<Components::LightComp>()->GetLight()->SetPos(BlueLight->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
    BlueLight->GetComponent<Components::LightComp>()->GetLight()->SetColor(1, 0, 1);

    DirLight->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(0, 60, 60));
    DirLight->AddComponent<Components::LightComp>()->GetLight()->SetPos(DirLight->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
    DirLight->GetComponent<Components::LightComp>()->GetLight()->SetColor(0.9, 0.9, 0.9);
    DirLight->GetComponent<Components::LightComp>()->GetLight()->SetDirectional(true);
    DirLight->GetComponent<Components::LightComp>()->GetLight()->SetIntensity(0.2f);

    flatTerrain->GetComponent<Components::TransformComp>()->GetTransform()->Rotate(glm::vec3(0, 0, 0));
    flatTerrain->GetComponent<Components::MaterialComp>()->GetMaterial()->SetColor(0.8f, 0.8f, 0.8f);

    Gear->GetComponent<Components::TransformComp>()->GetTransform()->Translate({ 0, 5, 0 });
    Torus->GetComponent<Components::TransformComp>()->GetTransform()->Translate({ 0, 5, 10 });
    Torus->GetComponent<Components::MaterialComp>()->GetMaterial()->SetColor(0, 1, 1);
    Torus->GetComponent<Components::MaterialComp>()->GetMaterial()->SetShininess(1);
    Gear->GetComponent<Components::MaterialComp>()->GetMaterial()->SetColor(0.4f, 0.4f, 0.4f);
    Gear->GetComponent<Components::MaterialComp>()->GetMaterial()->SetShininess(1);

    OrangeLight->GetComponent<Components::TransformComp>()->SetParent(Torus);
	//LoadScene(p_modelManager);
}

void Core::GameObjectManager::Update(float p_deltaTime)
{
    m_angle += 0.005f * p_deltaTime;
	if (Find("Torus") != nullptr)
	{
		Find("Torus")->GetComponent<Components::TransformComp>()->GetTransform()->Rotate(glm::vec3(0, 0, 1) * p_deltaTime);
		Find("Torus")->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(0, 0, -0.05) * p_deltaTime);
	}
	else
		std::cout << "ble\n";
    if (Find("BlueLight") != nullptr)
    {
        Find("BlueLight")->GetComponent<Components::TransformComp>()->GetTransform()->Rotate(glm::vec3(0, 1, 0) * p_deltaTime);
        Find("BlueLight")->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(0.1, 0, 0) * p_deltaTime);     
        Find("BlueLight")->GetComponent<Components::TransformComp>()->Update();
    }

    if (Find("Gear") != nullptr)
     Find("Gear")->GetComponent<Components::TransformComp>()->GetTransform()->Rotate(glm::vec3(1, 0, 0) * p_deltaTime);

    if (Find("OrangeLight") != nullptr)
        Find("OrangeLight")->GetComponent<Components::TransformComp>()->Update();

    for (auto& gameObject : m_gameObjects)
    {
        if (gameObject->GetComponent<Components::BoxColliderComp>() != nullptr)
        {
            gameObject->GetComponent<Components::BoxColliderComp>()->GetCollider()->GetPosVec() = gameObject->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition();
            gameObject->GetComponent<Components::BoxColliderComp>()->GetCollider()->GetMat() = gameObject->GetComponent<Components::TransformComp>()->GetTransform()->GetTransMat();
            gameObject->GetComponent<Components::BoxColliderComp>()->GetCollider()->UpdateBoundingBox();
        }
    }
    //Find("Torus")->CollidesWith(Find("Gear"));
}

int Core::GameObjectManager::LoadScene(const MeshManager& p_modelManager)
{
    using namespace tinyxml2;

    std::unordered_map<std::string, int> compTypes
    {
        {"BoxColliderComp", 0},
        {"LightComp", 1},
        {"MaterialComp", 2},
        {"ModelComp", 3},
        {"TransformComp", 4}
    };

#ifndef XMLCheckResult
#define XMLCheckResult(a_eResult) if (a_eResult != XML_SUCCESS) { std::cerr << "Error while parsing XML [LOADER] Error Type: " << a_eResult << '\n'; return a_eResult; }
#endif

    XMLDocument xmlDoc;
    XMLError    eResult = xmlDoc.LoadFile("scene.xml");
    XMLCheckResult(eResult);

    XMLNode* root = xmlDoc.FirstChild();
    if (root == nullptr)
        return XML_ERROR_FILE_READ_ERROR;

    XMLElement* GOList = root->FirstChildElement("GameObjectList");
    if (GOList == nullptr)
        return XML_ERROR_PARSING_ELEMENT;

    XMLElement* GOelement = GOList->FirstChildElement("GameObject");
    while (GOelement != nullptr)
    {
        const char* newGoName = nullptr;

        newGoName = GOelement->Attribute("name");
        if (newGoName == nullptr)
            return XML_ERROR_PARSING_ATTRIBUTE;

        int meshId{0}, shaderId{0};

        GOelement->QueryIntAttribute("mesh", &meshId);
        GOelement->QueryIntAttribute("shader", &shaderId);

        std::shared_ptr<GameObject> newGo = std::make_shared<GameObject
        >(p_modelManager.GetMesh(meshId), p_modelManager.GetShader(shaderId), newGoName);
        m_gameObjects.push_back(newGo);

        XMLElement* ComponentList = GOelement->FirstChildElement("ComponentList");
        if (GOelement == nullptr)
            return XML_ERROR_PARSING_ELEMENT;

        XMLElement* CompElement = ComponentList->FirstChildElement("Component");
        while (CompElement != nullptr)
        {
            const char* attribText = nullptr;

            attribText = CompElement->Attribute("type");
            if (attribText == nullptr)
                return XML_ERROR_PARSING_ATTRIBUTE;
            std::string newCompType{attribText};

            std::unordered_map<std::string, int>::const_iterator got = compTypes.find(newCompType);

            if (got == compTypes.end())
                std::cout << "component not found\n";
            else
            {
                switch (got->second)
                {
                case 0: //boxColliderComp
                    if (newGo->GetComponent<Components::BoxColliderComp>() == nullptr)
                        newGo->AddComponent<Components::BoxColliderComp>();

					newGo->GetComponent<Components::BoxColliderComp>()->Deserialize(CompElement);
                    break;
                case 1: //LightComp
                    if (newGo->GetComponent<Components::LightComp>() == nullptr)
                        newGo->AddComponent<Components::LightComp>();

					newGo->GetComponent<Components::LightComp>()->Deserialize(CompElement);
                    break;
                case 2: //materialComp
                    if (newGo->GetComponent<Components::MaterialComp>() == nullptr)
                        newGo->AddComponent<Components::MaterialComp>();

					newGo->GetComponent<Components::MaterialComp>()->Deserialize(CompElement);
                    break;
                case 3: //modelComp
                    if (newGo->GetComponent<Components::ModelComp>() == nullptr)
                        newGo->AddComponent<Components::ModelComp>();

					newGo->GetComponent<Components::ModelComp>()->Deserialize(CompElement);
                    break;
                case 4: //TransformComp
                    if (newGo->GetComponent<Components::TransformComp>() == nullptr)
                        newGo->AddComponent<Components::TransformComp>();

					newGo->GetComponent<Components::TransformComp>()->Deserialize(CompElement);
                    break;
                default:
                    std::cerr << "ERROR : something went wrong when trying to load components on the XML loader\n Your component type is non-existent.";
                    break;
                }
            }
            CompElement = CompElement->NextSiblingElement("Component");
        }
        GOelement = GOelement->NextSiblingElement("GameObject");
    }

    return EXIT_SUCCESS;
}

std::shared_ptr<Core::GameObject> Core::GameObjectManager::Find(const std::string& p_name)
{
    for (auto& m_gameObject : m_gameObjects)
    {
        if (m_gameObject->GetName() == p_name)
            return m_gameObject;
    }

	std::cout << "Could not find object " << p_name << "in Game Manager\n";
    return {};
}

std::vector<std::shared_ptr<Core::GameObject>>& Core::GameObjectManager::GetGameObjects() noexcept
{
	return m_gameObjects;
}

void Core::GameObjectManager::RemoveGameObject(std::shared_ptr<GameObject> p_gameObject)
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		if (m_gameObjects[i] == p_gameObject)
		{
			if (m_gameObjects[i]->GetComponent<Components::TransformComp>()->GetChild() != nullptr)
			{
				std::shared_ptr<GameObject> tmp = m_gameObjects[i]->GetChild();
				m_gameObjects[i]->GetComponent<Components::TransformComp>()->SetParent();
				RemoveGameObject(tmp);
			}

			m_gameObjects.erase(m_gameObjects.begin() + i);
			return;
		}
	}
}
