#pragma once
#include <AI/Grid.h>
#include <memory>

namespace Core::AI
{
    class PathFinding
    {
    public:
        PathFinding(int p_sizeX, int p_sizeY);
        ~PathFinding() = default;

        void FindNeighbors(Grid& p_grid, Dots& p_dot) const;

        std::unique_ptr<Grid> m_grid;
    };
}
