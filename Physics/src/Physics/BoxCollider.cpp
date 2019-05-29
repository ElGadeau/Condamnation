#include "stdafx.h"
#include <Physics/BoxCollider.h>


Physics::Collider::Collider(std::vector<glm::vec3>& p_vec) : m_points{ p_vec }
{
    m_modelMat = glm::mat4(1.0);
}


Physics::Collider::~Collider()
{

}
void Physics::Collider::SetBoundingBox()
{
    float m_maxX = 0;
    float m_minX = 0;
    float m_maxY = 0;
    float m_minY = 0;
    float m_maxZ = 0;
    float m_minZ = 0;

    for (unsigned int i = 0; i < m_points.size(); ++i)
    {
        glm::vec3 result = m_points[i];

        if (result.x > m_maxX)
            m_maxX = result.x;
        else if (result.x < m_minX)
            m_minX = result.x;

        if (result.y > m_maxY)
            m_maxY = result.y;
        else if (result.y < m_minY)
            m_minY = result.y;

        if (result.z > m_maxZ)
            m_maxZ = result.z;
        else if (result.z < m_minZ)
            m_minZ = result.z;
    }

    m_minVectmp = glm::vec4(m_minX, m_minY, m_minZ, 1.0);
    m_maxVectmp = glm::vec4(m_maxX, m_maxY, m_maxZ, 1.0);
}

void Physics::Collider::UpdateBoundingBox()
{
    m_maxVec = m_modelMat * m_maxVectmp;
    m_minVec = m_modelMat * m_minVectmp;
}

void Physics::Collider::PrintBoundingBox() const
{
	std::cout << "maxVec: " << m_maxVec.x << " / " << m_maxVec.y << " / " << m_maxVec.z << '\n';
	std::cout << "minVec: " << m_minVec.x << " / " << m_minVec.y << " / " << m_minVec.z << '\n';
    puts("-----------");
}