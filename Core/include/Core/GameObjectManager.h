#pragma once

#include <Core/GameObject.h>
#include <Core/MeshManager.h>

namespace Core
{
    class GameObjectManager
    {
    public:
        GameObjectManager() = default;
        GameObjectManager(MeshManager& p_modelManager);
        ~GameObjectManager() = default;

        void Update(const float& p_deltaTime);

        template<typename T>
        static unsigned int FindInstanceIteratorInVector(const T& p_object, const std::vector<T>& p_vector)
        {
            for (unsigned int i = 0; i < p_vector.size(); ++i)
            {
				if (p_object == p_vector[i])
					return i;
            }
			return -1;
        }

        int SaveScene(const MeshManager& p_modelManager);
        int LoadScene(const MeshManager& p_modelManager);
        std::shared_ptr<GameObject> Find(const std::string& p_name);
		[[nodiscard]] std::vector<std::shared_ptr<Core::GameObject>>& GetGameObjects() noexcept;
		void AddGameObject(GameObject& p_gameObject) { m_gameObjects.emplace_back(std::make_shared<GameObject>(p_gameObject)); }
		void RemoveGameObject(std::shared_ptr<GameObject> p_gameObject);
		void RemoveGameObject(const std::string& p_name);

    private:
        std::vector<std::shared_ptr<GameObject>> m_gameObjects;
        float m_angle{0.0f};
    };
}

