#include "stdafx.h"
#include <Core/GameObject.h>
#include <Rendering/Resources/Model.h>
#include <Components/include/ModelComp.h>
#include <Components/include/TransformComp.h>
#include <Components/include/LightComp.h>
#include <Rendering/Shader/Shader.h>
#include <Rendering/Resources/Loaders/ShaderLoader.h>
#include <Rendering/LowRenderer/Transform.h>
#include <Rendering/Shader/Shader.h>

float degree = 0;
Core::GameObject::GameObject()
{
    AddComponent<Components::TransformComp>();
    AddComponent<Components::ModelComp>();
}

Core::GameObject::GameObject(const std::string & p_meshPath, const std::string & p_vertPath, const std::string & p_fragPath)
{
    AddComponent<Components::TransformComp>();
    AddComponent<Components::ModelComp>()->m_model->SetMesh(Rendering::Resources::Model::LoadMesh(p_meshPath));
    GetComponent<Components::ModelComp>()->m_model->SetShader(Rendering::Resources::Loaders::ShaderLoader::LoadShader(p_vertPath, p_fragPath));
}

Core::GameObject::GameObject(std::shared_ptr<Rendering::Resources::Mesh> p_mesh, Rendering::Shaders::Shader* p_Shader)
{
    AddComponent<Components::TransformComp>();
    AddComponent<Components::ModelComp>()->m_model->SetMesh(p_mesh);
    GetComponent<Components::ModelComp>()->m_model->SetShader(p_Shader);
}

Core::GameObject::~GameObject()
{
    delete m_model;
}

void Core::GameObject::SetGameObjectMesh(std::shared_ptr<Rendering::Resources::Mesh> p_mesh)
{
    GetComponent<Components::ModelComp>()->m_model->SetMesh(p_mesh);
}

void Core::GameObject::SetModelShader(Rendering::Shaders::Shader& p_shader)
{
    GetComponent<Components::ModelComp>()->m_model->SetShader(&p_shader);
}

void Core::GameObject::Update(Rendering::LowRenderer::Camera & p_cam, std::vector<GameObject>& p_lights)
{
    std::vector<Rendering::LowRenderer::Light> m_lights;
    for (auto& light : p_lights)
    {
        m_lights.emplace_back(*light.GetComponent<Components::LightComp>()->m_light);
    }
    degree += 0.01f;
    GetComponent<Components::ModelComp>()->m_model->m_shader->ApplyShader();
    GetComponent<Components::ModelComp>()->m_model->m_shader->Update(p_cam, *GetComponent<Components::TransformComp>()->m_transform, m_lights);
}

void Core::GameObject::ReloadShader()
{
    std::string pathA = GetComponent<Components::ModelComp>()->m_model->GetShader()->m_vertPath;
    std::string pathB = GetComponent<Components::ModelComp>()->m_model->GetShader()->m_fragPath;

    GetComponent<Components::ModelComp>()->m_model->SetShader(Rendering::Resources::Loaders::ShaderLoader::LoadShader(pathA, pathB));
}
