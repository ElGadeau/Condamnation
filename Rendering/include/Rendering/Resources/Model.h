#pragma once
#include <Rendering/Export.h>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Shader/Shader.h>

namespace Rendering::Resources
{
    class API_RENDERING Model
    {
    public:
		Model();
        Model(const std::string& p_filePath);
        ~Model() { };

		static std::shared_ptr<Mesh> LoadMesh(const char* p_filePath);
		
		const std::shared_ptr<Shaders::Shader> GetShader() const noexcept { return m_shader; };
		void SetShader(std::shared_ptr<Shaders::Shader> p_shader);

		const std::shared_ptr<Mesh> GetMesh() const noexcept { return m_mesh; };
        void SetMesh(std::shared_ptr<Mesh> p_mesh);
        
        std::shared_ptr<Mesh> m_mesh;
		std::shared_ptr<Shaders::Shader> m_shader;
    };
}
