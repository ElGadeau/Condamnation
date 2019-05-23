#pragma once
#include <list>
#include <glm/vec3.hpp>

namespace Physics::AI
{
    class NavMesh
    {
    public:
        NavMesh();
        ~NavMesh();

        void FindNextPosition(glm::vec3& p_actualPosition, glm::vec3& p_target);



    private:
        std::list<glm::vec3> m_possiblePositions;
        glm::vec3 m_nextPosition;
    };
}
