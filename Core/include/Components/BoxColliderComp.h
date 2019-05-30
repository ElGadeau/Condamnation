#pragma once
#include <Components/Component.h>
#include <Physics/BoxCollider.h>
#include <glm/ext.hpp>

namespace Components
{
    class BoxColliderComp : public Component
    {
    public:
		BoxColliderComp(Core::GameObject& p_gameObject) : m_gameObject{ p_gameObject } {}
		~BoxColliderComp() = default;

        void SetCollider(std::vector<glm::vec3>& p_vec) { m_collider = std::make_shared<Physics::Collider>(p_vec); }
		[[nodiscard]] std::shared_ptr<Physics::Collider> GetCollider() const noexcept { return m_collider; }

    private:
        std::shared_ptr<Physics::Collider> m_collider;
        Core::GameObject& m_gameObject;
    };
}