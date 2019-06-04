#pragma once
#include <Components/Component.h>
#include <glm/vec3.hpp>

#include <Core/GameObject.h>
#include <Components/TransformComp.h>

namespace Components
{
	class BulletComp : public Component
	{
	public:
		BulletComp(Core::GameObject& p_gameObject, glm::vec3& p_direction, float p_speed, int p_damage) : m_gameObject{ p_gameObject },
			m_direction{ normalize(p_direction) }, m_speed{ p_speed }, m_damage{ p_damage } {}
		~BulletComp() = default;
		BulletComp(const BulletComp& p_other);

		void Update() override;

        void Serialize(XMLElement* p_compSegment) const noexcept override;
        void Deserialize(XMLElement* p_compSegment) const noexcept override;

	private:
		Core::GameObject& m_gameObject;
		glm::vec3 m_direction;
		float m_speed;
		int m_damage;
	};
}
