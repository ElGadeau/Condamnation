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
        using KeyCode = Utils::Event<int>::KeyCode;

        InputManager(const std::shared_ptr<Context::IWindow>&& p_window) noexcept;
        ~InputManager() noexcept;

        bool GetKeyDown(const KeyCode& p_keyCode);
        bool GetKeyUp(const KeyCode& p_keyCode);
        bool GetKey(const KeyCode& p_keyCode);

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

        std::unordered_map<int, std::string> m_inputBuffer;
    };
}
