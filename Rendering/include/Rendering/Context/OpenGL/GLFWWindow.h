#pragma once
#include <Rendering/Export.h>
#include <Rendering/Context/IWindow.h>
#include <Rendering/Utils/Event.h>

namespace Rendering::Context::OpenGL
{
    class API_RENDERING GLFWWindow : public IWindow
    {
    public:
        GLFWWindow();
        ~GLFWWindow();

        bool ShouldClose() const noexcept override;
        const std::any Data() const noexcept override;

    private:
        static GLFWWindow* GetInstance() noexcept;

        void BindKeyCallback() const noexcept;
        void BindMouseCallback() const noexcept;
        void BindMouseMovementCallback() const noexcept;

    private:
        static GLFWWindow* m_instance;
        GLFWwindow* m_glfwWindow;
    };
}