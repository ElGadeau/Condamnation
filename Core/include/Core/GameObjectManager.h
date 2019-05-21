#pragma once
#include <Core/GameObject.h>
#include <Core/MeshManager.h>
#include <Components/include/Component.h>
#include <Components/include/TransformComp.h>
#include <Components/include/LightComp.h>

namespace Core
{
    class GameObjectManager
    {
    public:
        GameObjectManager();
        GameObjectManager(Core::MeshManager& p_modelManager);
        ~GameObjectManager();
        std::vector<std::shared_ptr<Core::GameObject>> m_gameObjects;

        std::shared_ptr<Core::GameObject> Find(const std::string& p_name);
    };
}

