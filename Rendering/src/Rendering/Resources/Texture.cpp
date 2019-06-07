#include "stdafx.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <Rendering/Resources/Texture.h>
#include "iostream"


Texture::Texture() : m_data(nullptr), m_Width(0), m_Height(0), m_BPP(1)
{
    glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &m_texture);

}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::LoadTexture(const char* FilePath)
{


	m_data = stbi_load(FilePath, &m_Width, &m_Height, &m_BPP, STBI_rgb_alpha);

	if (m_data != nullptr)
	{


		std::cout << "Texture loaded: " << FilePath << "\n";
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
	else
	{
		std::cout << "Texture : " << FilePath << "not loaded" << "\n";
	}


}