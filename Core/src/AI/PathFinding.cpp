#include <AI/PathFinding.h>

Core::AI::PathFindind::PathFindind(int p_sizeX, int p_sizeY) : m_sizeX(p_sizeX), m_sizeY(p_sizeY)
{
    m_grid = new Dots*[m_sizeX];
    for (int i = 0; i < m_sizeX; ++i)
    {
        m_grid[i] = new Dots[m_sizeY];
    }

    for (int i = 0; i < m_sizeX; ++i)
    {
        for (int j = 0; j < m_sizeY; ++j)
        {
            m_grid[i][j].m_position = glm::vec3(i, j, 0);
        }
    }
}

Core::AI::PathFindind::~PathFindind()
{
    for (int i = 0; i < m_sizeX; ++i) 
    {
        delete[] m_grid[i];
    }
    delete[] m_grid;
}
