#pragma once
#include <Rendering/Export.h>
#include <Rendering/Context/IWindow.h>

namespace Rendering::Resources
{
    class API_RENDERING Texture
    {
    public:
        Texture();
	    ~Texture();
        void Bind();
	    void Unbind();
	    int GetWidth() const { return m_Width; }
	    int GetHeight() const { return m_Height; }
        int GetID() const { return m_texId; }
        void SetWidth(int p_width) { m_Width = p_width; }
        void SetHeight(int p_height) { m_Height = p_height; }

	    void Load(const char* Filename);

    private:
	    unsigned int m_texture;
	    unsigned char* m_data;
	    int m_Width, m_Height, m_BPP, m_texId;;
    };
}
