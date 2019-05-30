#pragma once

#include <vector>

#include <glm/glm.hpp>

namespace Core::AI
{
    class Dots
    {
    public:
        Dots();

        bool operator==(const Dots& p_right) const;

        void SetPosition(const glm::vec3& p_position);
        void SetIndexXY(int p_x, int p_y);

        const int& GetX() const;
        const int& GetY() const;
        const bool& GetIfWall() const;

        std::vector<Core::AI::Dots>& GetNeighbors();
        std::vector<Core::AI::Dots>& GetNeighboringWalls();

        void ShowIndex() const;
    private:
        int x;
        int y;

        float f;
        float g;
        float h;

        glm::vec3 m_position;
        std::vector<Dots> m_neighbors;
        std::vector<Dots> m_neighboringWalls;

        Dots* previous;

        bool isWall = false;

    };
}
