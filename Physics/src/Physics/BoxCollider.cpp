#include "stdafx.h"
#include <Physics/BoxCollider.h>


Physics::Collider::Collider(std::vector<glm::vec3>& p_vec) : m_points{ p_vec }
{
    m_maxX = 0.0f;
    m_minX = 0.0f;
    m_maxY = 0.0f;
    m_minY = 0.0f;
    m_maxZ = 0.0f;
    m_minZ = 0.0f;
    m_modelMat = glm::mat4(1.0f);
}


Physics::Collider::~Collider()
{

}

void Physics::Collider::UpdateBoundingBox()
{
    for (unsigned int i = 0; i < m_points.size(); ++i)
    {
        glm::mat4 tmp = m_modelMat;
        glm::vec4 result = tmp * glm::vec4(m_points[i], 1.0);

        if (result.x > m_maxX)
            m_maxX = result.x;

		if (i == 0)
		{
			m_minX = m_maxX;
			m_minY = m_maxY;
			m_minZ = m_maxZ;
			
		}

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

void Physics::Collider::PrintBoundingBox() const
{
	std::cout << "X: " << m_minX << ", " << m_maxX << "; Y: " << m_minY << ", " << m_maxY << "; Z: " << m_minZ << ", " << m_maxZ << '\n';
}