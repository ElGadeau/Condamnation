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
	// start make map
    std::shared_ptr<GameObject> Floor = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(0), p_modelManager.GetShader(0), "Floor");
    std::shared_ptr<GameObject> Wall1 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(0), p_modelManager.GetShader(0), "Wall1");
    std::shared_ptr<GameObject> Wall2 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(0), p_modelManager.GetShader(0), "Wall2");
    std::shared_ptr<GameObject> Wall3 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(0), p_modelManager.GetShader(0), "Wall3");
    std::shared_ptr<GameObject> Wall4 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(0), p_modelManager.GetShader(0), "Wall4");
    std::shared_ptr<GameObject> Ceiling = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(0), p_modelManager.GetShader(0), "Ceiling");
	
    Floor->GetComponent<Components::TransformComp>()->GetTransform()->Scale(glm::vec3(5, 1, 5));
	
    Wall1->GetComponent<Components::TransformComp>()->GetTransform()->Scale(glm::vec3(5, 1, 2));
	Wall1->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(0, 7, 48));
	Wall1->GetComponent<Components::TransformComp>()->GetTransform()->Rotate(glm::vec3(90, 0, 0));
	Wall1->GetComponent<Components::MaterialComp>()->GetMaterial()->SetColor(0.7f, 0.7f, 0.7f);

	Wall2->GetComponent<Components::TransformComp>()->GetTransform()->Scale(glm::vec3(5, 1, 2));
	Wall2->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(0, 7, -48));
	Wall2->GetComponent<Components::TransformComp>()->GetTransform()->Rotate(glm::vec3(90, 0, 0));
    
    Wall3->GetComponent<Components::TransformComp>()->GetTransform()->Scale(glm::vec3(5, 1, 5));
	Wall3->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(20, 7, 0));
	Wall3->GetComponent<Components::TransformComp>()->GetTransform()->Rotate(glm::vec3(90, 0, 90));
    
    Wall4->GetComponent<Components::TransformComp>()->GetTransform()->Scale(glm::vec3(5, 1, 5));
	Wall4->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(-19, 7, 0));
	Wall4->GetComponent<Components::TransformComp>()->GetTransform()->Rotate(glm::vec3(90, 0, 90));

	Ceiling->GetComponent<Components::TransformComp>()->GetTransform()->Scale(glm::vec3(5, 1, 5));
	Ceiling->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(0, 25, 0));
    // make map

    std::shared_ptr<GameObject> DirLight = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1),"Directionnal");
    std::shared_ptr<GameObject> OrangeLight = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "OrangeLight");
    std::shared_ptr<GameObject> BlueLight = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "BlueLight");

    //lights
    std::shared_ptr<GameObject> Torch1 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "Torch1");
    std::shared_ptr<GameObject> Torch2 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "Torch2");
    std::shared_ptr<GameObject> Torch3 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "Torch2");
    std::shared_ptr<GameObject> Torch4 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "Torch2");
	
    Torch1->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(90, 25, 90));
	Torch1->AddComponent<Components::LightComp>()->GetLight()->SetPos(Torch1->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
	Torch1->GetComponent<Components::LightComp>()->GetLight()->SetColor(0.9f, 0.7f, 0);
	Torch1->GetComponent<Components::LightComp>()->GetLight()->SetDirectional(true);
	Torch1->GetComponent<Components::LightComp>()->GetLight()->SetIntensity(0.2f);
    
    Torch2->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(-90, 25, -90));
	Torch2->AddComponent<Components::LightComp>()->GetLight()->SetPos(Torch2->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
	Torch2->GetComponent<Components::LightComp>()->GetLight()->SetColor(0.9f, 0.7f, 0);
	Torch2->GetComponent<Components::LightComp>()->GetLight()->SetDirectional(true);
	Torch2->GetComponent<Components::LightComp>()->GetLight()->SetIntensity(0.2f);
    
    Torch3->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(90, 25, -90));
	Torch3->AddComponent<Components::LightComp>()->GetLight()->SetPos(Torch3->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
	Torch3->GetComponent<Components::LightComp>()->GetLight()->SetColor(0.9f, 0.7f, 0);
	Torch3->GetComponent<Components::LightComp>()->GetLight()->SetDirectional(true);
	Torch3->GetComponent<Components::LightComp>()->GetLight()->SetIntensity(0.2f);
    
    Torch4->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(-90, 25, 90));
	Torch4->AddComponent<Components::LightComp>()->GetLight()->SetPos(Torch4->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
	Torch4->GetComponent<Components::LightComp>()->GetLight()->SetColor(0.9f, 0.7f, 0);
	Torch4->GetComponent<Components::LightComp>()->GetLight()->SetDirectional(true);
	Torch4->GetComponent<Components::LightComp>()->GetLight()->SetIntensity(0.2f);
    
    OrangeLight->GetComponent<Components::TransformComp>()->SetLocalTransformPos(glm::vec3(0, 4, 0));
    OrangeLight->AddComponent<Components::LightComp>()->GetLight()->SetPos(OrangeLight->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
    OrangeLight->GetComponent<Components::LightComp>()->GetLight()->SetColor(0, 1, 1);

    BlueLight->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(0, 2, 0));
    BlueLight->AddComponent<Components::LightComp>()->GetLight()->SetPos(BlueLight->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
    BlueLight->GetComponent<Components::LightComp>()->GetLight()->SetColor(1, 0, 1);

    DirLight->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(0, 25, 0));
    DirLight->AddComponent<Components::LightComp>()->GetLight()->SetPos(DirLight->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
    DirLight->GetComponent<Components::LightComp>()->GetLight()->SetColor(0.9f, 0.9f, 0.9f);
    DirLight->GetComponent<Components::LightComp>()->GetLight()->SetDirectional(true);
    DirLight->GetComponent<Components::LightComp>()->GetLight()->SetIntensity(0.9f);
    //end lights

    std::shared_ptr<GameObject> EmptyGameObject = std::make_shared<Core::GameObject>("Empty");

    std::shared_ptr<GameObject> Torus = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(3), p_modelManager.GetShader(0), "Torus");
    std::shared_ptr<GameObject> Gear = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(0), "Gear");

    m_gameObjects.push_back(Floor);
    m_gameObjects.push_back(Wall1);
    m_gameObjects.push_back(Wall2);
    m_gameObjects.push_back(Wall3);
    m_gameObjects.push_back(Wall4);
    //m_gameObjects.push_back(Ceiling);

    m_gameObjects.push_back(Torch1);
    m_gameObjects.push_back(Torch2);
    m_gameObjects.push_back(Torch3);
    m_gameObjects.push_back(Torch4);

    m_gameObjects.push_back(DirLight);
    m_gameObjects.push_back(OrangeLight);
    m_gameObjects.push_back(BlueLight);

    m_gameObjects.push_back(Torus);
    m_gameObjects.push_back(Gear);
    m_gameObjects.push_back(EmptyGameObject);



    Gear->GetComponent<Components::TransformComp>()->GetTransform()->Translate({ 0, 5, 0 });
    Torus->GetComponent<Components::TransformComp>()->GetTransform()->Translate({ 0, 5, 10 });
    Torus->GetComponent<Components::MaterialComp>()->GetMaterial()->SetColor(0, 1, 1);
    Torus->GetComponent<Components::MaterialComp>()->GetMaterial()->SetShininess(1);
    Gear->GetComponent<Components::MaterialComp>()->GetMaterial()->SetColor(0.4f, 0.4f, 0.4f);
    Gear->GetComponent<Components::MaterialComp>()->GetMaterial()->SetShininess(1);

    OrangeLight->GetComponent<Components::TransformComp>()->SetParent(Torus);
	//SaveScene(p_modelManager);
	//LoadScene(p_modelManager);
}

void Core::GameObjectManager::Update(const float& p_deltaTime)
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

int Core::GameObjectManager::SaveScene(const MeshManager& p_modelManager)
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
	XMLNode* root = xmlDoc.NewElement("Scene");
	xmlDoc.InsertFirstChild(root);

	XMLElement* GOList = xmlDoc.NewElement("GameObjectList");
	GOList->SetAttribute("count", static_cast<unsigned int>(m_gameObjects.size()));
	root->InsertFirstChild(GOList);

    for (auto gameObject : m_gameObjects)
    {
        XMLElement* GOelement = xmlDoc.NewElement("GameObject");
		GOelement->SetAttribute("name", gameObject->GetName().c_str());

        if (gameObject->GetComponent<Components::ModelComp>() != nullptr)
        {
            GOelement->SetAttribute("mesh", FindInstanceIteratorInVector(gameObject->GetComponent<Components::ModelComp>()->GetModel()->GetMesh(), p_modelManager.GetMeshes()));
            GOelement->SetAttribute("shader", FindInstanceIteratorInVector(gameObject->GetComponent<Components::ModelComp>()->GetModel()->GetShader(), p_modelManager.GetShaders()));
        }

        XMLElement* ComponentList = xmlDoc.NewElement("ComponentList");
	    ComponentList->SetAttribute("count", gameObject->GetComponentCount());


        for (const auto& component : gameObject->GetComponents())
        {
            XMLElement* CompElement = xmlDoc.NewElement("Component");
            std::string rawClassName = typeid(*component).name();
            int offset = rawClassName.find_last_of(':');
            std::string realName = rawClassName.substr(offset + 1);

            CompElement->SetAttribute("type", realName.c_str());

			component->Serialize(CompElement, xmlDoc);
            ComponentList->InsertEndChild(CompElement);
        }
		GOelement->InsertFirstChild(ComponentList);
        GOList->InsertEndChild(GOelement);
    }

	XMLError eResult = xmlDoc.SaveFile("newScene.xml");
	XMLCheckResult(eResult);
	return eResult;
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
    XMLError    eResult = xmlDoc.LoadFile("newScene.xml");
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
        m_gameObjects.push_back(newGo);
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
		if (*m_gameObjects[i] == *p_gameObject)
		{
			if (m_gameObjects[i]->GetComponent<Components::TransformComp>()->GetChild() != nullptr)
			{
				Core::GameObject& tmp = m_gameObjects[i]->GetComponent<Components::TransformComp>()->GetChild()->GetGameObject();
				m_gameObjects[i]->GetComponent<Components::TransformComp>()->GetChild()->SetParent();
				RemoveGameObject(std::make_shared<GameObject>(tmp));
				return;
			}
			
			m_gameObjects.erase(m_gameObjects.begin() + i);
			return;
		}
	}
}
