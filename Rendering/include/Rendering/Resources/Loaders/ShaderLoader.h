#pragma once
#include <iostream>
#include <Rendering/Export.h>
#include <Rendering/Shader/Shader.h>

namespace Rendering::Resources::Loaders
{
	class API_RENDERING ShaderLoader
	{
	public:
		ShaderLoader();
		~ShaderLoader();

		static Rendering::Shaders::Shader* LoadShader(const std::string& p_shaderPath, const std::string& p_shaderPathB);
	};
}
