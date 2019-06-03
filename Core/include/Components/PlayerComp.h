#pragma once
#include <Core/GameObject.h>
#include <Core/GameObjectManager.h>
#include <Rendering/Managers/InputManager.h>

namespace Components
{
	class PlayerComp : public Component
	{
	public:
		PlayerComp(Core::GameObject& p_gameObject, std::shared_ptr<Rendering::LowRenderer::Camera> p_camera, int p_health) :
			m_gameObject{ p_gameObject }, m_camera{ p_camera }, m_health { p_health } {}
		~PlayerComp() = default;

		void ProcessKeyInput(Core::GameObjectManager& p_gameManager, Rendering::Managers::InputManager & p_inputManager, const double & p_deltaTime);
		void Update() override;
		std::shared_ptr<Core::GameObject> RayCast(Core::GameObjectManager& p_gameManager);

	private:
		Core::GameObject& m_gameObject;
		std::shared_ptr<Rendering::LowRenderer::Camera> m_camera;
		int m_health;

	};
}
