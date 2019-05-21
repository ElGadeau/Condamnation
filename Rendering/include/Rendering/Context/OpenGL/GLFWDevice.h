#pragma once
#include <memory>

#include <Rendering/Context/IDevice.h>
#include <Rendering/Export.h>
#include <Rendering/Context/OpenGL/GLFWWindow.h>
#include "Rendering/LowRenderer/Camera.h"

namespace Rendering::Context::OpenGL
{
    class API_RENDERING GLFWDevice : public IDevice
    {
    public:
        GLFWDevice() noexcept;
        ~GLFWDevice() noexcept;

        void Init() noexcept override;
        bool ShouldClose() const noexcept override;
        void Render() const noexcept override;
        void RefreshEvents() const noexcept override;

        std::shared_ptr<GLFWWindow> GetWindow() const noexcept;

        void CalculateDeltaTime() noexcept;
        float GetDeltaTime() const noexcept;

    private:
        std::shared_ptr<GLFWWindow> m_window;

        float lastTime;
        float currentTime;
        float deltaTime;
        int MAX_FPS;

    };
}
