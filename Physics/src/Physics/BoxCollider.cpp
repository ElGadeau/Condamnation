#include "stdafx.h"
#include <Physics/BoxCollider.h>


Physics::Collider::Collider()
{
    m_maxX = 0;
    m_minX = 0;
    m_maxY = 0;
    m_minY = 0;
    m_maxZ = 0;
    m_minZ = 0;
}


Physics::Collider::~Collider()
{

}

void Physics::Collider::UpdateBoundingBox()
{
    for (unsigned int i = 0; i < m_points.size(); ++i)
    {
        glm::vec4 result = m_modelMat * glm::vec4(*m_points[i], 0.0);

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

}