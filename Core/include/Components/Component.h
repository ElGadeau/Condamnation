#pragma once

namespace Components
{
    class Component
    {
    public:
        Component();
        virtual ~Component() = default;

        static const size_t m_type;

        bool IsEqual(const size_t p_type) 
        {
            return p_type == m_type;
        }
    };
}

