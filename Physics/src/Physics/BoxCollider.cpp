#include "stdafx.h"
#include <Physics/BoxCollider.h>


Physics::Collider::Collider(std::vector<glm::vec3>& p_vec) : m_points{ p_vec }
{
    m_modelMat = glm::mat4(1.0f);
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

    maxVectmp = glm::vec4(m_maxX, m_maxY, m_maxZ, 1.0);
    minVectmp = glm::vec4(m_minX, m_minY, m_minZ, 1.0);
}

void Physics::Collider::UpdateBoundingBox()
{
    maxVec = m_modelMat * maxVectmp;
    minVec = m_modelMat * minVectmp;
}

void Physics::Collider::PrintBoundingBox() const
{
	std::cout << "maxVec: " << maxVec.x << " / " << maxVec.y << " / " << maxVec.z << '\n';
	std::cout << "minVec: " << minVec.x << " / " << minVec.y << " / " << minVec.z << '\n';
    puts("-----------");
}