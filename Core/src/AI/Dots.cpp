#include <AI/Dots.h>
#include <iostream>

Core::AI::Dots::Dots()
{
}

bool Core::AI::Dots::operator==(const Dots& p_right) const
{
    return (this == &p_right);
}

void Core::AI::Dots::SetPosition(const glm::vec3& p_position)
{
    m_position = p_position;
}

void Core::AI::Dots::SetIndexXY(int p_x, int p_y)
{
    x = p_x;
    y = p_y;
}

const int& Core::AI::Dots::GetX() const
{
    return x;
}

const int& Core::AI::Dots::GetY() const
{
    return y;
}

const bool& Core::AI::Dots::GetIfWall() const
{
    return isWall;
}

std::vector<Core::AI::Dots>& Core::AI::Dots::GetNeighbors()
{
    return m_neighbors;
}

std::vector<Core::AI::Dots>& Core::AI::Dots::GetNeighboringWalls()
{
    return m_neighboringWalls;
}

void Core::AI::Dots::ShowIndex() const
{
    std::cout << "x:" << x << " y:" << y << " | ";
}
