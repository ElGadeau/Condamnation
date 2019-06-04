#include "stdafx.h"
#include <string>

#include <Rendering/Resources/Model.h>
#include <Rendering/Resources/Loaders/ShaderLoader.h>
#include <Rendering/Shader/Shader.h>

#include <Core/GameObject.h>
#include <Components/ModelComp.h>
#include <Components/TransformComp.h>
#include <Components/LightComp.h>
#include <Components/MaterialComp.h>
#include <Components/BoxColliderComp.h>


Core::GameObject::GameObject()
{
    AddComponent<Components::TransformComp>();
}

Core::GameObject::GameObject(const char * p_name)
{
    AddComponent<Components::TransformComp>();
    m_name = p_name;
}

Core::GameObject::GameObject(const std::shared_ptr<Rendering::Resources::Mesh>& p_mesh, const std::shared_ptr<Rendering::Shaders::Shader>& p_shader, const char* p_name)
{
	m_name = p_name;
	AddComponent<Components::TransformComp>();

	AddComponent<Components::ModelComp>()->GetModel()->SetMesh(p_mesh);
	GetComponent<Components::ModelComp>()->GetModel()->SetShader(p_shader);

	AddComponent<Components::MaterialComp>();

	AddComponent<Components::BoxColliderComp>();

	GetComponent<Components::BoxColliderComp>()->SetCollider(GetComponent<Components::ModelComp>()->GetModel()->m_mesh->m_positions);
	GetComponent<Components::BoxColliderComp>()->GetCollider()->SetBoundingBox();
}

void Core::GameObject::SetGameObjectMesh(std::shared_ptr<Rendering::Resources::Mesh>& p_mesh)
{
    if(GetComponent<Components::ModelComp>() != nullptr)
        GetComponent<Components::ModelComp>()->GetModel()->SetMesh(p_mesh);
}

void Core::GameObject::SetModelShader(std::shared_ptr<Rendering::Shaders::Shader>& p_shader)
{
    if (GetComponent<Components::ModelComp>() != nullptr)
        GetComponent<Components::ModelComp>()->GetModel()->SetShader(p_shader);
}

void Core::GameObject::Update(Rendering::LowRenderer::Camera & p_cam, std::vector<GameObject>& p_lights)
{

    std::vector<Rendering::LowRenderer::Light> m_lights;
    for (auto& light : p_lights)
    {
        m_lights.emplace_back(*light.GetComponent<Components::LightComp>()->GetLight());
    }
    degree += 0.01f;

    if (GetComponent<Components::ModelComp>() != nullptr)
    {
        GetComponent<Components::ModelComp>()->GetModel()->m_shader->ApplyShader();
        GetComponent<Components::ModelComp>()->GetModel()->m_shader->Update(
        p_cam, 
        *GetComponent<Components::TransformComp>()->GetTransform(),
        *GetComponent<Components::MaterialComp>()->GetMaterial(), 
        m_lights.data(), m_lights.size());
    }

	for (auto& component : m_components)
	{
		component->Update();
	}
}

void Core::GameObject::ReloadShader()
{
    if (GetComponent<Components::ModelComp>() != nullptr)
    {
        const char* vertexPath = GetComponent<Components::ModelComp>()->GetModel()->GetShader()->m_vertPath;
        const char* fragPath = GetComponent<Components::ModelComp>()->GetModel()->GetShader()->m_fragPath;

        GetComponent<Components::ModelComp>()->GetModel()->SetShader(Rendering::Resources::Loaders::ShaderLoader::LoadShader(vertexPath, fragPath));
    }
}

bool Core::GameObject::CollidesWith(const std::shared_ptr<Core::GameObject>& p_gameObject)
{
    if (GetComponent<Components::BoxColliderComp>() == nullptr || p_gameObject->GetComponent<Components::BoxColliderComp>() == nullptr)
        return false;

    GetComponent<Components::BoxColliderComp>()->GetCollider()->UpdateBoundingBox();
    //GetComponent<Components::BoxColliderComp>()->GetCollider()->PrintBoundingBox();
    p_gameObject->GetComponent<Components::BoxColliderComp>()->GetCollider()->UpdateBoundingBox();

    Physics::Collider& colliderOne = *GetComponent<Components::BoxColliderComp>()->GetCollider();
    Physics::Collider& colliderTwo = *p_gameObject->GetComponent<Components::BoxColliderComp>()->GetCollider();

    bool isOverlapping = true;
    if (colliderOne.GetMaxVec().x < colliderTwo.GetMinVec().x || colliderOne.GetMinVec().x > colliderTwo.GetMaxVec().x)
        isOverlapping = false;
    if (colliderOne.GetMaxVec().y < colliderTwo.GetMinVec().y || colliderOne.GetMinVec().y > colliderTwo.GetMaxVec().y)
        isOverlapping = false;
    if (colliderOne.GetMaxVec().z < colliderTwo.GetMinVec().z || colliderOne.GetMinVec().z > colliderTwo.GetMaxVec().z)
        isOverlapping = false;

    if(isOverlapping)
    {
        std::cout << m_name << "Collided with " << p_gameObject->m_name << "\n";
        return true;
    }

    return false;
}

void Core::GameObject::ResolveCollisions(std::vector<std::shared_ptr<Core::GameObject>>& p_gameObjects)
{
    //TODO : resolve collisions for physics simulation

    /*for (unsigned int k = 0; k < p_gameObjects.size(); ++k)
    {
        p_gameObjects[k]->GetComponent<Components::BoxColliderComp>()->GetCollider()->UpdateBoundingBox();
       // p_gameObjects[k]->GetComponent<Components::BoxColliderComp>()->m_collider->PrintBoundingBox();
    }

    for (unsigned int i = 0; i < p_gameObjects.size(); ++i)
    {
        for (unsigned int j = 0; j < p_gameObjects.size(); ++j)
        {
            if (p_gameObjects[i]->m_name != p_gameObjects[j]->m_name)
            {
                Physics::Collider& colliderOne = *p_gameObjects[i]->GetComponent<Components::BoxColliderComp>()->GetCollider();
                Physics::Collider& colliderTwo = *p_gameObjects[j]->GetComponent<Components::BoxColliderComp>()->GetCollider();

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

bool Core::operator==(GameObject& p_1, GameObject& p_2)
{
	if (p_1.GetName() == p_2.GetName())
		return true;

	return false;
}
