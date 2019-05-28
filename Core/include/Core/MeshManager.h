#pragma once
#include <Rendering/Resources/Mesh.h>
#include <Core/GameObject.h>
#include <Rendering/Shader/Shader.h>

namespace Core
{
    class MeshManager
    {
    public:
        MeshManager() = default;
        ~MeshManager() = default;

        void AddMesh(const char* p_filePath);
        void AddShader(const char* p_vertPath, const char* p_fragPath);
        void ReloadShader(std::vector<std::shared_ptr<GameObject>>& p_gameObjects);
        void LoadMeshes();
        void LoadShaders();

        std::shared_ptr<Rendering::Resources::Mesh> GetMesh(const int& p_position) const noexcept { return meshes[p_position];}
		Rendering::Shaders::Shader* GetShader(const int& p_position) const noexcept { return shaders[p_position];	}

    private:
        std::vector<std::shared_ptr<Rendering::Resources::Mesh>> meshes;
        std::vector<Rendering::Shaders::Shader*> shaders;
	};

}
