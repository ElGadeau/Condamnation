#pragma once

namespace Components
{
    class Component
    {
    public:
        Component() = default;
        virtual ~Component() = default;
		virtual void Update() = 0;
        static const size_t m_type = 0;

        bool IsEqual(const size_t p_type) 
        {
            return p_type == m_type;
        }
    };
}

