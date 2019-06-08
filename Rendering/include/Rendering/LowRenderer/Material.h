#pragma once

#include <Rendering/Export.h>
#include <Rendering/Resources/Texture.h>

namespace Rendering::LowRenderer
{
    class API_RENDERING Material
    {
    public:

        Material() 
        { 
            m_shininess = 0.0f;
            m_r = 1; 
            m_g = 1; 
            m_b = 1; 
            m_opacity = 1; 
        };
        ~Material() {};

        void SetColor(const float& p_red, const float& p_green, const float& p_blue) { m_r = p_red; m_g = p_green; m_b = p_blue; };
        void SetShininess(const float& p_shininess) { m_shininess = p_shininess; };
        void SetOpacity(const float& p_opacity) { m_opacity = p_opacity; };
        void LoadTexture(const char* p_filePath);
        void SetTextureActive();


		const float& GetShininess() const noexcept { return m_shininess; }
		const float& GetOpacity() const noexcept { return m_opacity; }
        Rendering::Resources::Texture& GetTexture() { return m_tex; }

		const float& GetColorR() const noexcept { return m_r; }
		const float& GetColorG() const noexcept { return m_g; }
		const float& GetColorB() const noexcept { return m_b; }

    private:
        float m_shininess;
        float m_opacity;

        Rendering::Resources::Texture m_tex;
        float m_r;
        float m_g;
        float m_b;
    };
}
