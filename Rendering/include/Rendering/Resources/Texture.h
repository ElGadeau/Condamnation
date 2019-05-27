#pragma once
#include <Rendering/Export.h>
#include <Rendering/Context/IWindow.h>

class API_RENDERING Texture
{
public:
	Texture();
	~Texture();

	void Bind() const;
	void Unbind() const;

	void LoadTexture(const std::string& p_filepath);
	bool texture_is_set() const { return m_loaded; }

private:
	GLuint m_id{ 0u };
	bool m_loaded;

};
