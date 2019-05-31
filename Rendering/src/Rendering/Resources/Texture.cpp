#include "stdafx.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <Rendering/Resources/Texture.h>
#include "iostream"


Texture::Texture() :m_texture(0), m_data(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{

	glGenTextures(1, &m_texture);
	Bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	Unbind();

}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind(unsigned slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::LoadTexture(const std::string& FilePath)
{
	stbi_set_flip_vertically_on_load(1);
	m_data = stbi_load(FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

	if (m_data != nullptr)
	{
		std::cout << "Texture loaded: " << FilePath.c_str() << "\n";
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
	}
	else
	{
		std::cout << "Texture : " << FilePath.c_str() << "not loaded" << "\n";
	}


}