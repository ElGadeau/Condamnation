#pragma once
#include "stdafx.h"
#include <Core/GameObject.h>
#include <Core/GameObjectManager.h>

namespace Utils
{
	std::shared_ptr<Core::GameObject> RayCast(std::shared_ptr<Core::GameObject> p_origin, const glm::vec3& p_direction, Core::GameObjectManager& p_gameManager);
	std::shared_ptr<Core::GameObject> RayCast(Core::GameObject& p_origin, const glm::vec3& p_direction, Core::GameObjectManager& p_gameManager);
}
