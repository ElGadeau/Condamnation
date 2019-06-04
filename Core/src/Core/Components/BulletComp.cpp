#include <Components/BulletComp.h>

Components::BulletComp::BulletComp(const BulletComp& p_other) : m_gameObject{ p_other.m_gameObject }, m_direction { p_other.m_direction }
{
	m_damage = p_other.m_damage;
	m_speed = p_other.m_speed;
}

void Components::BulletComp::Serialize(XMLElement* p_compSegment) const noexcept
{
	std::cout << "[BULLET_COMP] Function not implemented\n";
}

void Components::BulletComp::Deserialize(XMLElement* p_compSegment) const noexcept
{
	std::cout << "[BULLET_COMP] Function not implemented\n";
}
