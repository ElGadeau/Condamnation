#pragma once
#include <GL/glew.h>
#include <Rendering/Export.h>
#include <Rendering/Context/IDriver.h>
#include <Core/GameObject.h>
#include <Rendering/Managers/CameraManager.h>

namespace Rendering::Managers
{
    class API_RENDERING Renderer
    {
    public:
        Renderer() noexcept = default;

        template<typename T>
        void Initialize()
        {
            static_assert(std::is_base_of_v<Context::IDriver, T>);

            m_driver = std::make_unique<T>();
            m_driver->EnableDebug();
        }

        void Clear() const noexcept;
        void PolygoneModeLine() const noexcept;
        void PolygoneModeFill() const noexcept;

		void SetupCulling();
        void Draw(Resources::Mesh& m_mesh) const noexcept;

    private:
        std::unique_ptr<Context::IDriver> m_driver;
        GLuint program;

    };
}
