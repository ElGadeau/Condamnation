#pragma once
#include <Rendering/Export.h>
#include <Rendering/Context/IWindow.h>

class API_RENDERING Texture
{
public:
	Texture();
	~Texture();
    void Bind();
	void Unbind();
	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
    void SetWidth(int p_width) { m_Width = p_width; }
    void SetHeight(int p_height) { m_Height = p_height; }

	void LoadTexture(const char* Filename);

private:
	GLuint m_texture;
	unsigned char* m_data;
	int m_Width, m_Height, m_BPP;
};
