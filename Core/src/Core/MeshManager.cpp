#include <Core/MeshManager.h>
#include <Core/GameObject.h>
#include <Rendering/Resources/Model.h>
#include <Rendering/Resources/Loaders/ShaderLoader.h>
#include <Rendering/Shader/Shader.h>

Core::MeshManager::MeshManager()
{
}

Core::MeshManager::~MeshManager()
{
}

void Core::MeshManager::AddMesh(const char* p_filePath)
{
    meshes.push_back(Rendering::Resources::Model::LoadMesh(p_filePath));
}

void Core::MeshManager::AddShader(const char* p_vertPath, const char* p_fragPath)
{
    shaders.push_back(Rendering::Resources::Loaders::ShaderLoader::LoadShader(p_vertPath, p_fragPath));
}

void Core::MeshManager::ReloadShader(std::vector<std::shared_ptr<Core::GameObject>>& p_gameObjects)
{
    for (int i = 0; i < shaders.size(); ++i)
    {
        const char* pathA = shaders[i]->m_vertPath;
        const char* pathB = shaders[i]->m_fragPath;

        shaders[i] = Rendering::Resources::Loaders::ShaderLoader::LoadShader(pathA, pathB);
    }

    for (auto& gameObject : p_gameObjects)
        gameObject->ReloadShader();
}

void Core::MeshManager::LoadMeshes()
{
    AddMesh(R"(..\Resources\Meshes\plane2.obj)");
    AddMesh(R"(..\Resources\Meshes\sphere.fbx)");
    AddMesh(R"(..\Resources\Meshes\plane.fbx)");
    AddMesh(R"(..\Resources\Meshes\torus.fbx)");
    AddMesh(R"(..\Resources\Meshes\gear.fbx)");
    AddMesh(R"(..\Resources\Meshes\boby.fbx)");
    AddMesh(R"(..\Resources\Meshes\monster.obj)");
}

void Core::MeshManager::LoadShaders()
{
    AddShader("../Resources/Shaders/vertShader.vert", "../Resources/Shaders/fragShader2.frag");
    AddShader("../Resources/Shaders/vertShader.vert", "../Resources/Shaders/lightShader.frag");
}

std::shared_ptr<Rendering::Resources::Mesh> Core::MeshManager::GetMesh(int p_position)
{
    return meshes[p_position];
}

Rendering::Shaders::Shader* Core::MeshManager::GetShader(int p_position)
{
    return shaders[p_position];
}

