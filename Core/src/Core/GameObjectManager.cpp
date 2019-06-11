#include <tinyxml2.h>

#include <Core/GameObjectManager.h>
#include <Components/LightComp.h>
#include <Components/TransformComp.h>
#include <Components/MaterialComp.h>
#include <Components/BoxColliderComp.h>
#include <Components/RigidBodyComp.h>
#include <Components/ModelComp.h>

#include <unordered_map>

Core::GameObjectManager::GameObjectManager(MeshManager& p_modelManager)
{
    std::shared_ptr<GameObject> Castle = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(0), p_modelManager.GetShader(0), "Castle");
    std::shared_ptr<GameObject> Gun = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(2), p_modelManager.GetShader(0), "Gun");
    std::shared_ptr<GameObject> Floor = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(3), p_modelManager.GetShader(0), "Floor");
    std::shared_ptr<GameObject> Wall1 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(3), p_modelManager.GetShader(0), "Wall1");
    std::shared_ptr<GameObject> Wall2 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(3), p_modelManager.GetShader(0), "Wall2");
    std::shared_ptr<GameObject> Wall3 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(3), p_modelManager.GetShader(0), "Wall3");
    std::shared_ptr<GameObject> Wall4 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(3), p_modelManager.GetShader(0), "Wall4");
    std::shared_ptr<GameObject> Wall5 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(3), p_modelManager.GetShader(0), "Wall5");
    std::shared_ptr<GameObject> Ramp = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(3), p_modelManager.GetShader(0), "Ramp");
    std::shared_ptr<GameObject> Ceiling = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(3), p_modelManager.GetShader(0), "Ceiling");

    // start make map
	Floor->GetComponent<Components::TransformComp>()->GetTransform()->Scale({ 5, 1, 5 });
	Floor->AddComponent<Components::BoxColliderComp>()->SetCollider(Floor->GetComponent<Components::ModelComp>()->GetModel()->GetMesh()->m_positions);
	Floor->AddComponent<Components::RigidBodyComp>(this)->SetKinematic(true);
	Floor->GetComponent<Components::MaterialComp>()->GetMaterial()->LoadTexture("../Resources/Textures/bricks.jpg");

	Wall1->GetComponent<Components::TransformComp>()->GetTransform()->Translate({ 0, 5, 99 });
	Wall1->AddComponent<Components::RigidBodyComp>(this)->SetKinematic(true);
	Wall1->GetComponent<Components::MaterialComp>()->GetMaterial()->LoadTexture("../Resources/Textures/bricks.jpg");
	Wall1->GetComponent<Components::TransformComp>()->GetTransform()->Rotate({ 90, 0, 0 });
	Wall1->AddComponent<Components::BoxColliderComp>()->SetCollider(Wall1->GetComponent<Components::ModelComp>()->GetModel()->GetMesh()->m_positions);
	Wall1->GetComponent<Components::TransformComp>()->GetTransform()->Scale({ 5, 0.5, 1 });

	Wall2->GetComponent<Components::TransformComp>()->GetTransform()->Translate({ 0, 5, -99 });
	Wall2->AddComponent<Components::RigidBodyComp>(this)->SetKinematic(true);
	Wall2->GetComponent<Components::MaterialComp>()->GetMaterial()->LoadTexture("../Resources/Textures/bricks.jpg");
	Wall2->GetComponent<Components::TransformComp>()->GetTransform()->Rotate({ 90, 0, 0 });
	Wall2->AddComponent<Components::BoxColliderComp>()->SetCollider(Wall2->GetComponent<Components::ModelComp>()->GetModel()->GetMesh()->m_positions);
	Wall2->GetComponent<Components::TransformComp>()->GetTransform()->Scale({ 5, 0.5, 1 });

	Wall3->GetComponent<Components::TransformComp>()->GetTransform()->Translate({ 99, 5, 0 });
	Wall3->AddComponent<Components::RigidBodyComp>(this)->SetKinematic(true);
	Wall3->GetComponent<Components::MaterialComp>()->GetMaterial()->LoadTexture("../Resources/Textures/bricks.jpg");
	Wall3->GetComponent<Components::TransformComp>()->GetTransform()->Rotate({ 90, 0, 90 });
	Wall3->AddComponent<Components::BoxColliderComp>()->SetCollider(Wall3->GetComponent<Components::ModelComp>()->GetModel()->GetMesh()->m_positions);
	Wall3->GetComponent<Components::TransformComp>()->GetTransform()->Scale({ 5, 0.5, 1 });

	Wall4->GetComponent<Components::TransformComp>()->GetTransform()->Translate({ -99, 5, 0 });
	Wall4->AddComponent<Components::RigidBodyComp>(this)->SetKinematic(true);
	Wall4->GetComponent<Components::MaterialComp>()->GetMaterial()->LoadTexture("../Resources/Textures/bricks.jpg");
	Wall4->GetComponent<Components::TransformComp>()->GetTransform()->Rotate({ 90, 0, 90 });
	Wall4->AddComponent<Components::BoxColliderComp>()->SetCollider(Wall4->GetComponent<Components::ModelComp>()->GetModel()->GetMesh()->m_positions);
	Wall4->GetComponent<Components::TransformComp>()->GetTransform()->Scale({ 5, 0.5, 1 });

	Wall5->GetComponent<Components::TransformComp>()->GetTransform()->Translate({ 0, 5, 0 });
	Wall5->AddComponent<Components::RigidBodyComp>(this)->SetKinematic(true);
	Wall5->GetComponent<Components::MaterialComp>()->GetMaterial()->LoadTexture("../Resources/Textures/bricks.jpg");
	Wall5->GetComponent<Components::TransformComp>()->GetTransform()->Rotate({ 90, 0, 0 });
	Wall5->AddComponent<Components::BoxColliderComp>()->SetCollider(Wall5->GetComponent<Components::ModelComp>()->GetModel()->GetMesh()->m_positions);
	Wall5->GetComponent<Components::TransformComp>()->GetTransform()->Scale({ 3, 0.2, 1 });

	Ramp->GetComponent<Components::TransformComp>()->GetTransform()->Translate({ -80, 8, -90 });
	Ramp->AddComponent<Components::RigidBodyComp>(this)->SetKinematic(true);
	Ramp->GetComponent<Components::MaterialComp>()->GetMaterial()->LoadTexture("../Resources/Textures/bricks.jpg");
	Ramp->GetComponent<Components::TransformComp>()->GetTransform()->Rotate({ 0, 90, 0 });
	Ramp->GetComponent<Components::TransformComp>()->GetTransform()->Rotate({ 22, 90, 0 });
	Ramp->AddComponent<Components::BoxColliderComp>()->SetCollider(Ramp->GetComponent<Components::ModelComp>()->GetModel()->GetMesh()->m_positions);
	Ramp->GetComponent<Components::TransformComp>()->GetTransform()->Scale({ 1.2, 0.2, 0.56 });

	Ceiling->GetComponent<Components::TransformComp>()->GetTransform()->Translate({0, 13, 20});
	Ceiling->AddComponent<Components::RigidBodyComp>(this)->SetKinematic(true);
	Ceiling->GetComponent<Components::MaterialComp>()->GetMaterial()->LoadTexture("../Resources/Textures/bricks.jpg");
	Ceiling->GetComponent<Components::TransformComp>()->GetTransform()->Scale({ 5, 1, 5 });
	Ceiling->AddComponent<Components::BoxColliderComp>()->SetCollider(Ceiling->GetComponent<Components::ModelComp>()->GetModel()->GetMesh()->m_positions);
    // end make map

    std::shared_ptr<GameObject> DirLight = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "Directionnal");
    std::shared_ptr<GameObject> OrangeLight = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "OrangeLight");
    std::shared_ptr<GameObject> BlueLight = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "BlueLight");

    //lights
    std::shared_ptr<GameObject> Torch1 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "Torch1");
    std::shared_ptr<GameObject> Torch2 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "Torch2");
    std::shared_ptr<GameObject> Torch3 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "Torch3");
    std::shared_ptr<GameObject> Torch4 = std::make_shared<Core::GameObject>(p_modelManager.GetMesh(1), p_modelManager.GetShader(1), "Torch4");

    Torch1->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(60, 25, 60));
    Torch1->AddComponent<Components::LightComp>()->GetLight()->SetPos(Torch1->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
    Torch1->GetComponent<Components::LightComp>()->GetLight()->SetColor(1, 0, 0);
    Torch1->GetComponent<Components::LightComp>()->GetLight()->SetDirectional(false);
    Torch1->GetComponent<Components::LightComp>()->GetLight()->SetIntensity(400);

    Torch2->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(-60, 25, -60));
    Torch2->AddComponent<Components::LightComp>()->GetLight()->SetPos(Torch2->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
    Torch2->GetComponent<Components::LightComp>()->GetLight()->SetColor(0, 1, 0);
    Torch2->GetComponent<Components::LightComp>()->GetLight()->SetDirectional(false);
    Torch2->GetComponent<Components::LightComp>()->GetLight()->SetIntensity(400);

    Torch3->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(60, 25, -60));
    Torch3->AddComponent<Components::LightComp>()->GetLight()->SetPos(Torch3->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
    Torch3->GetComponent<Components::LightComp>()->GetLight()->SetColor(0, 0, 1);
    Torch3->GetComponent<Components::LightComp>()->GetLight()->SetDirectional(false);
    Torch3->GetComponent<Components::LightComp>()->GetLight()->SetIntensity(400);

    Torch4->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(-60, 25, 60));
    Torch4->AddComponent<Components::LightComp>()->GetLight()->SetPos(Torch4->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
    Torch4->GetComponent<Components::LightComp>()->GetLight()->SetColor(1, 0, 1);
    Torch4->GetComponent<Components::LightComp>()->GetLight()->SetDirectional(false);
    Torch4->GetComponent<Components::LightComp>()->GetLight()->SetIntensity(400);

    OrangeLight->GetComponent<Components::TransformComp>()->SetLocalTransformPos(glm::vec3(0, 4, 0));
    OrangeLight->AddComponent<Components::LightComp>()->GetLight()->SetPos(OrangeLight->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
    OrangeLight->GetComponent<Components::LightComp>()->GetLight()->SetColor(0, 1, 1);
    OrangeLight->GetComponent<Components::LightComp>()->GetLight()->SetIntensity(10.0f);

    BlueLight->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(0, 40, 0));
    BlueLight->AddComponent<Components::LightComp>()->GetLight()->SetPos(BlueLight->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
    BlueLight->GetComponent<Components::LightComp>()->GetLight()->SetColor(1, 1, 0);
    BlueLight->GetComponent<Components::LightComp>()->GetLight()->SetIntensity(400.0f);

    DirLight->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(0, 25, 0));
    DirLight->AddComponent<Components::LightComp>()->GetLight()->SetPos(DirLight->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition());
    DirLight->GetComponent<Components::LightComp>()->GetLight()->SetColor(0.0f, 0.0f, 0.0f);
    DirLight->GetComponent<Components::LightComp>()->GetLight()->SetDirectional(true);
    DirLight->GetComponent<Components::LightComp>()->GetLight()->SetIntensity(0.0);
    //end lights

    Castle->GetComponent<Components::TransformComp>()->GetTransform()->SetPosition({10, 5, 10});
    Castle->GetComponent<Components::MaterialComp>()->GetMaterial()->LoadTexture("../Resources/Textures/youngLink.png");
    Castle->GetComponent<Components::TransformComp>()->GetTransform()->Scale({0.05, 0.05, 0.05});
    Castle->AddComponent<Components::BoxColliderComp>()->SetCollider(Castle->GetComponent<Components::ModelComp>()->GetModel()->GetMesh()->m_positions);
	Castle->AddComponent<Components::RigidBodyComp>(this);

    Gun->GetComponent<Components::MaterialComp>()->GetMaterial()->LoadTexture("../Resources/Textures/huntinggun.png");
    Gun->GetComponent<Components::TransformComp>()->GetTransform()->Scale({10, 10, 10});

    m_gameObjects.push_back(Floor);
    m_gameObjects.push_back(Wall1);
    m_gameObjects.push_back(Wall2);
    m_gameObjects.push_back(Wall3);
    m_gameObjects.push_back(Wall4);
    m_gameObjects.push_back(Wall5);
    m_gameObjects.push_back(Ramp);
    m_gameObjects.push_back(Ceiling);

    m_gameObjects.push_back(Torch1);
    m_gameObjects.push_back(Torch2);
    m_gameObjects.push_back(Torch3);
    m_gameObjects.push_back(Torch4);

    m_gameObjects.push_back(DirLight);
    m_gameObjects.push_back(OrangeLight);
    m_gameObjects.push_back(BlueLight);

    m_gameObjects.push_back(Castle);
    m_gameObjects.push_back(Gun);
	//LoadScene(p_modelManager);
	SaveScene(p_modelManager, "CastleScene");
}

void Core::GameObjectManager::Update(const float& p_deltaTime)
{

    m_angle += 0.005f * p_deltaTime;
    if (Find("BlueLight") != nullptr)
    {
        Find("BlueLight")->GetComponent<Components::TransformComp>()->GetTransform()->Rotate(glm::vec3(0, 1, 0) * p_deltaTime);
        Find("BlueLight")->GetComponent<Components::TransformComp>()->GetTransform()->Translate(glm::vec3(0.1, 0, 0) * p_deltaTime);     
        Find("BlueLight")->GetComponent<Components::TransformComp>()->Update();
    }

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
}

int Core::GameObjectManager::SaveScene(const MeshManager& p_modelManager, const std::string& p_scenename)
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
	XMLNode* root = xmlDoc.NewElement("scene");
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
            size_t offset = rawClassName.find_last_of(':');
            std::string realName = rawClassName.substr(offset + 1);

            CompElement->SetAttribute("type", realName.c_str());

			component->Serialize(CompElement, xmlDoc);
            ComponentList->InsertEndChild(CompElement);
        }
		GOelement->InsertFirstChild(ComponentList);
        GOList->InsertEndChild(GOelement);
    }

	XMLError eResult = xmlDoc.SaveFile(p_scenename.c_str());
	XMLCheckResult(eResult);
	return eResult;
}

int Core::GameObjectManager::LoadScene(const MeshManager& p_modelManager, const std::string& p_sceneName)
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
    XMLError    eResult = xmlDoc.LoadFile(p_sceneName.c_str());
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
        int meshId{0}, shaderId{0};
        bool empty{ true };

        newGoName = GOelement->Attribute("name");
        if (newGoName == nullptr)
            return XML_ERROR_PARSING_ATTRIBUTE;

        eResult = GOelement->QueryIntAttribute("mesh", &meshId);
        if (eResult == XML_SUCCESS)
            empty = false;
        
        eResult = GOelement->QueryIntAttribute("shader", &shaderId);
        if (eResult == XML_SUCCESS)
            empty = false;

        std::shared_ptr<GameObject> newGo{};

        if(!empty)
            newGo = std::make_shared<GameObject>(p_modelManager.GetMesh(meshId), p_modelManager.GetShader(shaderId), newGoName);
        else if(empty)
            newGo = std::make_shared<GameObject>(newGoName);
                
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
                    break;
                case 4: //TransformComp
                    if (newGo->GetComponent<Components::TransformComp>() == nullptr)
                        newGo->AddComponent<Components::TransformComp>();

                    newGo->GetComponent<Components::TransformComp>()->Deserialize(CompElement);
                    break;
                default:
                    std::cerr <<
                            "ERROR : something went wrong when trying to load components on the XML loader\n Your component type is non-existent.";
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
