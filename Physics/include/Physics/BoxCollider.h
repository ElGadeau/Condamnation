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

		[[nodiscard]] glm::vec4& GetMaxVecTmp() noexcept { return m_maxVectmp; }
		[[nodiscard]] glm::vec4& GetMinVecTmp() noexcept { return m_minVectmp; }
		[[nodiscard]] glm::vec4& GetMaxVec() noexcept { return m_minVec; }
		[[nodiscard]] glm::vec4& GetMinVec() noexcept { return m_minVec; }
		[[nodiscard]] glm::mat4& GetModelMat() noexcept { return m_modelMat; }
		[[nodiscard]] std::vector<glm::vec3>& GetPoints() const noexcept { return m_points; }

    private:
        glm::vec4 m_maxVectmp;
        glm::vec4 m_minVectmp;
        glm::vec4 m_maxVec;
        glm::vec4 m_minVec;

        glm::mat4 m_modelMat;

        std::vector<glm::vec3>& m_points;
    };
}

