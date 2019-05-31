#pragma once
#include <Rendering/Export.h>
#include <Rendering/Context/IWindow.h>

class API_RENDERING Texture
{
public:
	Texture();
	~Texture();
	void Bind(unsigned int slot = 0)const;
	void Unbind();
	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }
	void LoadTexture(const std::string& Filename);

private:
	GLuint m_texture;
	unsigned char* m_data;
	int m_Width, m_Height, m_BPP;
};
