#include "stdafx.h"

#include <Physics/BoxCollider.h>

Physics::Collider::Collider(std::vector<glm::vec3>& p_vec) : m_points{ p_vec }
{
    m_pos = glm::vec3(0, 0, 0);
}

void Physics::Collider::SetBoundingBox()
{
    float m_maxX = 0;
    float m_minX = 0;
    float m_maxY = 0;
    float m_minY = 0;
    float m_maxZ = 0;
    float m_minZ = 0;

    for (auto& result : m_points)
    {
        if (result.x > m_maxX)
            m_maxX = result.x;
        if (result.x < m_minX)
            m_minX = result.x;

        if (result.y > m_maxY)
            m_maxY = result.y;
        if (result.y < m_minY)
            m_minY = result.y;

        if (result.z > m_maxZ)
            m_maxZ = result.z;
        if (result.z < m_minZ)
            m_minZ = result.z;
    }

    m_minVectmp = glm::vec4(m_minX, m_minY, m_minZ, 1.0);
    m_maxVectmp = glm::vec4(m_maxX, m_maxY, m_maxZ, 1.0);
}

void Physics::Collider::UpdateBoundingBox()
{
    m_maxVec = glm::vec4(m_pos, 1.0) + m_maxVectmp;
    m_minVec = glm::vec4(m_pos, 1.0) + m_minVectmp;
}

void Physics::Collider::PrintBoundingBox() const
{
	std::cout << "maxVec: " << m_maxVec.x << " / " << m_maxVec.y << " / " << m_maxVec.z << '\n';
	std::cout << "minVec: " << m_minVec.x << " / " << m_minVec.y << " / " << m_minVec.z << '\n';
    puts("-----------");
}