#pragma once
#include <AI/Dots.h>

namespace Core::AI
{
    class PathFindind
    {
    public:
        PathFindind(int p_sizeX, int p_sizeY);
        ~PathFindind();

        Dots** m_grid;

    private:
        int m_sizeX;
        int m_sizeY;
    };
}
