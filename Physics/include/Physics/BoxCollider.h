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

        void SetBoundingBox();
        void UpdateBoundingBox();
		void PrintBoundingBox() const;

        glm::vec4 maxVectmp;
        glm::vec4 minVectmp;
        glm::vec4 maxVec;
        glm::vec4 minVec;

        glm::mat4* m_modelMat;

        std::vector<glm::vec3>& m_points;
    };
}

