#pragma once
#include <string>
#include <Rendering/Resources/Mesh.h>
#include <Core/GameObject.h>
#include <Rendering/Shader/Shader.h>

namespace Core
{
    class MeshManager
    {
    public:
        MeshManager();
        ~MeshManager();

        std::vector<std::shared_ptr<Rendering::Resources::Mesh>> meshes;
        std::vector<Rendering::Shaders::Shader*> shaders;

        void AddMesh(const char* p_filePath);
        void AddShader(const char* p_vertPath, const char* p_fragPath);
        void ReloadShader(std::vector<std::shared_ptr<Core::GameObject>>& p_gameObjects);
        void LoadMeshes();
        void LoadShaders();

        std::shared_ptr<Rendering::Resources::Mesh> GetMesh(const int& p_position);
        Rendering::Shaders::Shader* GetShader(const int& p_position);
    };

}
