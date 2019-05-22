#pragma once
#include <Core/GameObject.h>
#include <Core/MeshManager.h>
#include <Components/Component.h>
#include <Components/TransformComp.h>
#include <Components/LightComp.h>

namespace Core
{
    class GameObjectManager
    {
    public:
        GameObjectManager();
        GameObjectManager(Core::MeshManager& p_modelManager);
        ~GameObjectManager();
        std::vector<std::shared_ptr<Core::GameObject>> m_gameObjects;
        void Update(float deltaTime);
        std::shared_ptr<Core::GameObject> Find(const std::string& p_name);
    };
}

