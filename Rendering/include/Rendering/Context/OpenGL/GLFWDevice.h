#pragma once

#include <memory>

#include <Rendering/Context/IDevice.h>
#include <Rendering/Export.h>
#include <Rendering/Context/OpenGL/GLFWWindow.h>

namespace Rendering::Context::OpenGL
{
    class API_RENDERING GLFWDevice : public IDevice
    {
    public:
        GLFWDevice() noexcept;
        ~GLFWDevice() noexcept;

        void Init() noexcept override;
        bool ShouldClose() const noexcept override;
        
        void CalculateDeltaTime() noexcept;
        
        void RefreshEvents() const noexcept override;
        void Render() const noexcept override;
        		
		std::shared_ptr<GLFWWindow> GetWindow() const noexcept { return m_window; }
		const double& GetDeltaTime() const noexcept { return deltaTime; }
        		
        void Close() const noexcept;

    private:
        std::shared_ptr<GLFWWindow> m_window{};

        double lastTime = 0;
        double currentTime = 0;
        double deltaTime = 0;
        int MAX_FPS = 0;

    };
}
