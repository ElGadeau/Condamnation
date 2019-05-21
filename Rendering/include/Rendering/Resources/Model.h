#pragma once
#include <Rendering/Export.h>
#include <Rendering/Resources/Mesh.h>
#include <Rendering/Shader/Shader.h>
#include <Rendering/LowRenderer/Camera.h>
#include <Rendering/LowRenderer/Transform.h>

namespace Rendering::Resources
{
    class API_RENDERING Model
    {
    public:
		Model();
        Model(const std::string & p_filePath);
        ~Model() { };

		static std::shared_ptr<Rendering::Resources::Mesh> LoadMesh(const std::string& p_filePath);
		
		Shaders::Shader* GetShader();
		void SetShader(Rendering::Shaders::Shader* p_shader);

        std::shared_ptr<Rendering::Resources::Mesh> GetMesh();
        void SetMesh(std::shared_ptr<Rendering::Resources::Mesh> p_mesh);
        
        std::shared_ptr<Rendering::Resources::Mesh> m_mesh;
        Shaders::Shader* m_shader;

    private:

    };
}
