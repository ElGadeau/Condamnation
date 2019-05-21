#pragma once
#include <memory>
#include <list>

#include <Rendering/Context/IWindow.h>
#include <Rendering/Export.h>

namespace Rendering::Managers
{
    class API_RENDERING InputManager
    {
    public:
        InputManager(const std::shared_ptr<Context::IWindow>&& p_window) noexcept;
        ~InputManager() noexcept;

        std::list<int> GetKeyInputList();
        glm::vec2 GetMouseInputList();

    private:
        void OnKeyPressed(int p_key);
        void OnKeyReleased(int p_key);
        void OnMouseButtonPressed(int p_button);
        void OnMouseButtonReleased(int p_button);
        void OnMouseMovement(double p_xPos, double p_yPos);

    private:
        std::shared_ptr<Context::IWindow> m_window;

        std::list<int> m_keyInputList;
        glm::vec2 m_MouseInputList;

        uint8_t m_idKeyPressedListener;
        uint8_t m_idKeyReleasedListener;
        uint8_t m_idMouseButtonPressedListener;
        uint8_t m_idMouseButtonReleasedListener;
        uint8_t m_idMouseMovedListener;
    };
}
