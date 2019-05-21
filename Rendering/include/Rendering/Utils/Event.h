#pragma once
#include <unordered_map>
#include <functional>

namespace Rendering::Utils
{
    template<typename ... Types>
    class Event
    {
    public:
        using callback = std::function<void(Types...)>;
        using callback_id = uint8_t;

        void Invoke(Types... p_args)
        {
            for (const auto&[id, callback] : m_callbacks)
                callback(p_args...);
        }

        callback_id AddListener(callback p_callback) noexcept
        {
            callback_id id = m_availableListener++;
            m_callbacks.emplace(id, p_callback);
            return id;
        }

        bool RemoveListener(callback_id p_id) noexcept
        {
            return m_callbacks.erase(p_id) != 0;
        }

        void RemoveAllListener() noexcept
        {
            m_callbacks.clear();
        }

    private:
        callback_id m_availableListener{0u};
        std::pmr::unordered_map<callback_id, callback> m_callbacks;
    };
}
