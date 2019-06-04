#include <Components/PlayerComp.h>
#include <Components/BulletComp.h>
#include <Core/GameObjectManager.h>
#include "Components/ModelComp.h"
#include <Components/BoxColliderComp.h>
#include "Utils/Ray.h"

void Components::PlayerComp::ProcessKeyInput(Core::GameObjectManager& p_gameManager, Rendering::Managers::InputManager & p_inputManager, const double & p_deltaTime)
{
	if (p_inputManager.GetKey(Rendering::Managers::InputManager::KeyCode::Space))
	{
		std::shared_ptr<Core::GameObject> collision = Utils::RayCast(m_gameObject, m_camera->GetFront(), p_gameManager);
		if (collision != nullptr)
		{
			p_gameManager.RemoveGameObject(collision);
		}
	}
}

void Components::PlayerComp::Update()
{
	m_gameObject.GetComponent<TransformComp>()->GetTransform()->SetPosition(m_camera->GetPosition());
}

std::shared_ptr<Core::GameObject> Components::PlayerComp::RayCast(Core::GameObjectManager& p_gameManager) const
{
	glm::vec3 currPos = m_gameObject.GetComponent<TransformComp>()->GetTransform()->GetPosition() + m_camera->GetFront();
	glm::vec3 cameraFront = glm::normalize(m_camera->GetFront());
	cameraFront.x /= 10.0f;
	cameraFront.y /= 10.0f;
	cameraFront.z /= 10.0f;

	//std::cout << "camera front: " << m_camera->GetFront().x << ", " << m_camera->GetFront().y << ", " << m_camera->GetFront().z << '\n';

	for (int i = 0; i < 100; ++i)
	{
		for (auto& gameObject : p_gameManager.GetGameObjects())
		{
			if (&*gameObject == &m_gameObject ||
				 glm::distance(gameObject->GetComponent<TransformComp>()->GetTransform()->GetPosition(), 
					 m_gameObject.GetComponent<TransformComp>()->GetTransform()->GetPosition()) > 100 ||
				gameObject->GetComponent<TransformComp>() == nullptr ||
				gameObject->GetComponent<ModelComp>() == nullptr ||
				gameObject->GetComponent<BoxColliderComp>() == nullptr)
				continue;

			currPos = currPos + cameraFront;
			glm::vec4 minVec = gameObject->GetComponent<BoxColliderComp>()->GetCollider()->GetMinVec();
			glm::vec4 maxVec = gameObject->GetComponent<BoxColliderComp>()->GetCollider()->GetMaxVec();
			//gameObject->GetComponent<BoxColliderComp>()->GetCollider()->PrintBoundingBox();

			if (maxVec.x > currPos.x && minVec.x < currPos.x &&
				maxVec.y > currPos.y && minVec.y < currPos.y &&
				maxVec.z > currPos.z && minVec.z < currPos.z)
			{
				std::cout << m_gameObject.GetName() << " raycast collision with " << gameObject->GetName() << '\n';
				return gameObject;
			}
			
		}
	}
		return {};
}

void Components::PlayerComp::Serialize(XMLElement* p_compSegment) const noexcept
{
	std::cout << "[PLAYER_COMP] Function not implemented\n";
}

void Components::PlayerComp::Deserialize(XMLElement* p_compSegment) const noexcept
{
	std::cout << "[PLAYER_COMP] Function not implemented\n";
}
