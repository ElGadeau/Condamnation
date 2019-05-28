#pragma once
#include <vector>
#include <Physics/Export.h>
#include <glm/ext.hpp>

namespace Physics
{
    class API_PHYSICS Collider
    {
    public:
        Collider(std::vector<glm::vec3>& p_vec);
        ~Collider();

        void UpdateBoundingBox();
		void PrintBoundingBox();

        float m_maxX;
        float m_minX;
        float m_maxY;
        float m_minY;
        float m_maxZ;
        float m_minZ;

        glm::mat4 m_modelMat;
        std::vector<glm::vec3>& m_points;
    };
}

