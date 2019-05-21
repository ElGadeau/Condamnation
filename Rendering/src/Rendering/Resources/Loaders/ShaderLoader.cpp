#include "stdafx.h"
#include <Rendering/Resources/Loaders/ShaderLoader.h>
#include <Rendering/Shader/Shader.h>

Rendering::Resources::Loaders::ShaderLoader::ShaderLoader()
{
}

Rendering::Resources::Loaders::ShaderLoader::~ShaderLoader()
{
}

Rendering::Shaders::Shader * Rendering::Resources::Loaders::ShaderLoader::LoadShader(const std::string & p_shaderPath, const std::string & p_shaderPathB)
{
	Rendering::Shaders::Shader* m_shader = new Rendering::Shaders::Shader{};
    m_shader->m_vertPath = p_shaderPath;
    m_shader->m_fragPath = p_shaderPathB;

	m_shader->Load(p_shaderPath, GL_VERTEX_SHADER, p_shaderPathB, GL_FRAGMENT_SHADER);

	return m_shader;
}
