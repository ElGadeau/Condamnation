#include <Components/BulletComp.h>

Components::BulletComp::BulletComp(const BulletComp& p_other) : m_gameObject{ p_other.m_gameObject }, m_direction { p_other.m_direction }
{
	m_damage = p_other.m_damage;
	m_speed = p_other.m_speed;
}
