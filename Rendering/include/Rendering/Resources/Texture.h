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
	void LoadTexture(const std::string& fileName);
private:

	GLuint m_texture;
};
