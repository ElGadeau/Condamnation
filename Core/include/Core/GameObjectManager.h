#pragma once

#include <Core/GameObject.h>
#include <Core/MeshManager.h>

namespace Core
{
    class GameObjectManager
    {
    public:
        GameObjectManager() = default;
        GameObjectManager(Core::MeshManager& p_modelManager);
        ~GameObjectManager() = default;

        void Update(float p_deltaTime);
        int LoadScene();
        std::shared_ptr<Core::GameObject> Find(const std::string& p_name);
		[[nodiscard]] std::vector<std::shared_ptr<Core::GameObject>>& GetGameObjects() noexcept;
		void AddGameObject(GameObject& p_gameObject) { m_gameObjects.emplace_back(std::make_shared<GameObject>(p_gameObject)); }
		void RemoveGameObject(std::shared_ptr<GameObject> p_gameObject);
		void RemoveGameObject(const std::string& p_name);

    private:
        std::vector<std::shared_ptr<Core::GameObject>> m_gameObjects;
        float m_angle;
    };
}

