#include "stdafx.h"
#include <string>

#include <Core/GameObject.h>
#include <Components/ModelComp.h>
#include <Components/TransformComp.h>
#include <Components/LightComp.h>
#include <Components/MaterialComp.h>
#include <Components/BoxColliderComp.h>

#include <Rendering/Resources/Model.h>
#include <Rendering/Resources/Loaders/ShaderLoader.h>

#include <Rendering/LowRenderer/Transform.h>
#include <Rendering/Shader/Shader.h>

float degree = 0;
Core::GameObject::GameObject()
{
    AddComponent<Components::TransformComp>();
    AddComponent<Components::ModelComp>();
    AddComponent<Components::MaterialComp>();

    AddComponent<Components::BoxColliderComp>()->m_collider->m_points = GetComponent<Components::ModelComp>()->m_model->m_mesh->m_positions;
    GetComponent<Components::BoxColliderComp>()->m_collider->m_modelMat = &GetComponent<Components::TransformComp>()->m_transform->m_transMat;
}

Core::GameObject::GameObject(const char* p_meshPath, const char* p_vertPath, const char* p_fragPath)
{
    AddComponent<Components::TransformComp>();

    AddComponent<Components::ModelComp>()->m_model->SetMesh(Rendering::Resources::Model::LoadMesh(p_meshPath));
    GetComponent<Components::ModelComp>()->m_model->SetShader(Rendering::Resources::Loaders::ShaderLoader::LoadShader(p_vertPath, p_fragPath));

    AddComponent<Components::MaterialComp>();

    AddComponent<Components::BoxColliderComp>()->m_collider->m_points = GetComponent<Components::ModelComp>()->m_model->m_mesh->m_positions;
    GetComponent<Components::BoxColliderComp>()->m_collider->m_modelMat = &GetComponent<Components::TransformComp>()->m_transform->m_transMat;
}

Core::GameObject::GameObject(std::shared_ptr<Rendering::Resources::Mesh> p_mesh, Rendering::Shaders::Shader* p_Shader, const char* p_name)
{
    m_name = p_name;
    AddComponent<Components::TransformComp>();

    AddComponent<Components::ModelComp>()->m_model->SetMesh(p_mesh);
    GetComponent<Components::ModelComp>()->m_model->SetShader(p_Shader);

    AddComponent<Components::MaterialComp>();

    AddComponent<Components::BoxColliderComp>();
    GetComponent<Components::BoxColliderComp>()->SetCollider(GetComponent<Components::ModelComp>()->m_model->m_mesh->m_positions);
    GetComponent<Components::BoxColliderComp>()->m_collider->SetBoundingBox();
    GetComponent<Components::BoxColliderComp>()->m_collider->m_modelMat = &GetComponent<Components::TransformComp>()->m_transform->m_transMat;
}

Core::GameObject::~GameObject()
{
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
    GetComponent<Components::ModelComp>()->m_model->m_shader->Update(
        p_cam, 
        *GetComponent<Components::TransformComp>()->m_transform, 
        *GetComponent<Components::MaterialComp>()->m_material, 
        m_lights.data(), m_lights.size());
}

void Core::GameObject::ReloadShader()
{
    const char* pathA = GetComponent<Components::ModelComp>()->m_model->GetShader()->m_vertPath;
    const char* pathB = GetComponent<Components::ModelComp>()->m_model->GetShader()->m_fragPath;

    GetComponent<Components::ModelComp>()->m_model->SetShader(Rendering::Resources::Loaders::ShaderLoader::LoadShader(pathA, pathB));
}

bool Core::GameObject::CollidesWith(const std::shared_ptr<Core::GameObject>& p_gameObject)
{
    GetComponent<Components::BoxColliderComp>()->m_collider->UpdateBoundingBox();
    p_gameObject->GetComponent<Components::BoxColliderComp>()->m_collider->UpdateBoundingBox();

    if (m_name != p_gameObject->m_name)
    {
        Physics::Collider& colliderOne = *GetComponent<Components::BoxColliderComp>()->m_collider;
        Physics::Collider& colliderTwo = *p_gameObject->GetComponent<Components::BoxColliderComp>()->m_collider;

        bool isOverlapping = true;
        if (colliderOne.maxVec.x < colliderTwo.minVec.x || colliderOne.minVec.x > colliderTwo.maxVec.x)
            isOverlapping = false;
        if (colliderOne.maxVec.y < colliderTwo.minVec.y || colliderOne.minVec.y > colliderTwo.maxVec.y)
            isOverlapping = false;
        if (colliderOne.maxVec.z < colliderTwo.minVec.z || colliderOne.minVec.z > colliderTwo.maxVec.z)
            isOverlapping = false;

        if(isOverlapping)
        {
            std::cout << m_name << " Collided with " << p_gameObject->m_name << std::endl;
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

void Core::GameObject::ResolveCollisions(std::vector<std::shared_ptr<Core::GameObject>>& p_gameObjects)
{
    //TODO : resolve collisions for physics simulation

    /*for (unsigned int k = 0; k < p_gameObjects.size(); ++k)
    {
        p_gameObjects[k]->GetComponent<Components::BoxColliderComp>()->m_collider->m_modelMat = p_gameObjects[k]->GetComponent<Components::TransformComp>()->m_transform->m_transMat;
        p_gameObjects[k]->GetComponent<Components::BoxColliderComp>()->m_collider->UpdateBoundingBox();
    }

    for (unsigned int i = 0; i < p_gameObjects.size(); ++i)
    {
        for (unsigned int j = 0; j < p_gameObjects.size(); ++j)
        {
            if (p_gameObjects[i]->m_name != p_gameObjects[j]->m_name)
            {
                Physics::Collider& colliderOne = *p_gameObjects[i]->GetComponent<Components::BoxColliderComp>()->m_collider;
                Physics::Collider& colliderTwo = *p_gameObjects[j]->GetComponent<Components::BoxColliderComp>()->m_collider;

                bool isOverlapping = true;
                if (colliderOne.maxVec.x < colliderTwo.minVec.x || colliderOne.minVec.x > colliderTwo.maxVec.x)
                    isOverlapping = false;
                if (colliderOne.maxVec.y < colliderTwo.minVec.y || colliderOne.minVec.y > colliderTwo.maxVec.y)
                    isOverlapping = false;
                if (colliderOne.maxVec.z < colliderTwo.minVec.z || colliderOne.minVec.z > colliderTwo.maxVec.z)
                    isOverlapping = false;

                if (isOverlapping)
                {
                    std::cout << p_gameObjects[i]->m_name << " Collided with " << p_gameObjects[j]->m_name << std::endl;
                    puts(" ");
                }
            }
        }
    }*/
}
