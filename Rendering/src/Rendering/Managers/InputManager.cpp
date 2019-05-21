#include "stdafx.h"
#include <Rendering/Managers/InputManager.h>
#include <Rendering/Managers/CameraManager.h>

Rendering::Managers::InputManager::InputManager(
    const std::shared_ptr<Context::IWindow>&& p_window) noexcept
    : m_window{p_window}
{
    m_idKeyPressedListener = p_window->m_keyPressedEvent.AddListener(
        std::bind(&InputManager::OnKeyPressed, this, std::placeholders::_1));

    m_idKeyReleasedListener = p_window->m_keyReleasedEvent.AddListener(
        std::bind(&InputManager::OnKeyReleased, this, std::placeholders::_1));

    m_idMouseButtonPressedListener = p_window->m_mouseButtonPressedEvent.AddListener(
        std::bind(&InputManager::OnMouseButtonPressed, this, std::placeholders::_1));

    m_idMouseButtonReleasedListener = p_window->m_mouseButtonReleasedEvent.AddListener(
        std::bind(&InputManager::OnMouseButtonReleased, this, std::placeholders::_1));

    m_idMouseMovedListener = p_window->m_mouseMoved.AddListener(
        std::bind(&InputManager::OnMouseMovement, this, std::placeholders::_1, std::placeholders::_2));
}

Rendering::Managers::InputManager::~InputManager() noexcept
{
    assert(m_window->m_keyPressedEvent.RemoveListener(m_idKeyPressedListener));
    assert(m_window->m_keyReleasedEvent.RemoveListener(m_idKeyReleasedListener));
    assert(m_window->m_mouseButtonPressedEvent.RemoveListener(m_idMouseButtonPressedListener));
    assert(m_window->m_mouseButtonReleasedEvent.RemoveListener(m_idMouseButtonReleasedListener));
    assert(m_window->m_mouseMoved.RemoveListener(m_idMouseMovedListener));
}

bool Rendering::Managers::InputManager::GetKeyDown(const KeyCode& p_keyCode)
{
    if (!(m_inputBuffer.find(p_keyCode) == m_inputBuffer.end()))
        if (m_inputBuffer.find(p_keyCode)->second == "KeyDown")
        {
            m_inputBuffer.at(p_keyCode) = "Complete";
            return true;
        }
    return false;

}

bool Rendering::Managers::InputManager::GetKeyUp(const KeyCode& p_keyCode)
{
    if (!(m_inputBuffer.find(p_keyCode) == m_inputBuffer.end()))
        if (m_inputBuffer.find(p_keyCode)->second == "KeyUp")
        {
            m_inputBuffer.at(p_keyCode) = "Complete";
            return true;
        }
    return false;
}

bool Rendering::Managers::InputManager::GetKey(const KeyCode& p_keyCode)
{
    if (!(m_inputBuffer.find(p_keyCode) == m_inputBuffer.end()))
        if (m_inputBuffer.find(p_keyCode)->second == "KeyDown")
            return true;
    return false;
}

glm::vec2 Rendering::Managers::InputManager::GetMouseInputList()
{
    return m_MouseInputList;
}

void Rendering::Managers::InputManager::OnKeyPressed(int p_key)
{
    /*if (p_key == 256)
        glfwSetWindowShouldClose(std::any_cast<GLFWwindow*>(m_window->Data()), true);*/


    m_inputBuffer.insert_or_assign(p_key, "KeyDown");
}

void Rendering::Managers::InputManager::OnKeyReleased(int p_key)
{
    m_inputBuffer.insert_or_assign(p_key, "KeyUp");
}

void Rendering::Managers::InputManager::OnMouseButtonPressed(int p_button)
{
    m_keyInputList.emplace_back(p_button);
}

void Rendering::Managers::InputManager::OnMouseButtonReleased(int p_button)
{
    m_keyInputList.remove(p_button);
}

void Rendering::Managers::InputManager::OnMouseMovement(double p_xPos, double p_yPos)
{
    m_MouseInputList.x = p_xPos;
    m_MouseInputList.y = p_yPos;
    glfwSetCursorPos(std::any_cast<GLFWwindow*>(m_window->Data()), 1920 / 2, 1080 / 2);
}
