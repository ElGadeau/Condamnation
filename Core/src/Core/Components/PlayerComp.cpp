#include <Components/PlayerComp.h>
#include <Components/BulletComp.h>
#include <Core/GameObjectManager.h>
#include "Components/ModelComp.h"
#include <Components/BoxColliderComp.h>

void Components::PlayerComp::ProcessKeyInput(Core::GameObjectManager& p_gameManager, Rendering::Managers::InputManager & p_inputManager, const double & p_deltaTime)
{
	if (p_inputManager.GetKey(Rendering::Managers::InputManager::KeyCode::Space))
	{
		RayCast(p_gameManager);
	}
}

void Components::PlayerComp::Update()
{
	//m_gameObject.GetComponent<TransformComp>()->SetLocalTransformPos(m_camera.GetPosition());
	m_gameObject.GetComponent<TransformComp>()->GetTransform()->SetPosition(m_camera->GetPosition());
}

std::shared_ptr<Core::GameObject> Components::PlayerComp::RayCast(Core::GameObjectManager& p_gameManager)
{
	glm::vec3 currPos = m_gameObject.GetComponent<TransformComp>()->GetTransform()->GetPosition();

	std::cout << "camera front: " << m_camera->GetFront().x << ", " << m_camera->GetFront().y << ", " << m_camera->GetFront().z << '\n';

	for (int i = 0; i < 100; ++i)
	{

		for (auto& gameObject : p_gameManager.GetGameObjects())
		{
			if (gameObject->GetName() == "Torus")
			{
				std::cout << gameObject->GetName() << '\n';
				gameObject->GetComponent<BoxColliderComp>()->GetCollider()->PrintBoundingBox();
				if (gameObject->GetComponent<BoxColliderComp>()->GetCollider()->GetMaxVec().x > currPos.x &&
					gameObject->GetComponent<BoxColliderComp>()->GetCollider()->GetMinVec().x < currPos.x &&
					gameObject->GetComponent<BoxColliderComp>()->GetCollider()->GetMaxVec().y > currPos.y &&
					gameObject->GetComponent<BoxColliderComp>()->GetCollider()->GetMinVec().y < currPos.y &&
					gameObject->GetComponent<BoxColliderComp>()->GetCollider()->GetMaxVec().z > currPos.z &&
					gameObject->GetComponent<BoxColliderComp>()->GetCollider()->GetMinVec().z < currPos.z)
				{
					std::cout << m_gameObject.GetName() << " raycast collision with " << gameObject->GetName() << '\n';
					return gameObject;
				}
			}
			glm::vec3 cameraFront = glm::normalize(m_camera->GetFront());
			cameraFront.x /= 10.0f;
			cameraFront.y /= 10.0f;
			cameraFront.z /= 10.0f;
			currPos = currPos + (cameraFront);
		}
	}
		return nullptr;
}
