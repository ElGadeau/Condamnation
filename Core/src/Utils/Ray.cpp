#include <Utils/Ray.h>
#include <Components/TransformComp.h>
#include <Components/BoxColliderComp.h>
#include "Components/ModelComp.h"

std::shared_ptr<Core::GameObject> Utils::RayCast(std::shared_ptr<Core::GameObject> p_origin, const glm::vec3& p_direction, Core::GameObjectManager& p_gameManager)
{
	glm::vec3 currPos = p_origin->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition();
	glm::vec3 direction = glm::normalize(p_direction);
	direction.x /= 10.0f;
	direction.y /= 10.0f;
	direction.z /= 10.0f;

	for (int i = 0; i < 100; ++i)
	{
		for (auto& gameObject : p_gameManager.GetGameObjects())
		{
			if (gameObject == p_origin
				|| glm::distance(gameObject->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition(),
					p_origin->GetComponent<Components::TransformComp>()->GetTransform()->GetPosition()) > 100 ||
				gameObject->GetComponent<Components::TransformComp>() == nullptr ||
				gameObject->GetComponent<Components::ModelComp>() == nullptr ||
				gameObject->GetComponent<Components::BoxColliderComp>() == nullptr)
				continue;

			currPos = currPos + direction;
			glm::vec4 minVec = gameObject->GetComponent<Components::BoxColliderComp>()->GetCollider()->GetMinVec();
			glm::vec4 maxVec = gameObject->GetComponent<Components::BoxColliderComp>()->GetCollider()->GetMaxVec();
			//gameObject->GetComponent<BoxColliderComp>()->GetCollider()->PrintBoundingBox();

			if (maxVec.x > currPos.x && minVec.x < currPos.x &&
				maxVec.y > currPos.y && minVec.y < currPos.y &&
				maxVec.z > currPos.z && minVec.z < currPos.z)
			{
				std::cout << p_origin->GetName() << " raycast collision with " << gameObject->GetName() << '\n';
				return gameObject;
			}

		}
	}
	return nullptr;
}
