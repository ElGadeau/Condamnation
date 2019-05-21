#include <PhysX/BulletEngine.h>
#include <Components/include/RigidBodyComp.h>
#include <Components/include/TransformComp.h>
#include <iostream>
#include <cassert>

using namespace Core::PhysX;

BulletEngine::BulletEngine()
{
    Init();

    //assert(m_instance == nullptr);
    //m_instance = this;
}

BulletEngine::~BulletEngine()
{
    for (int i = m_dynamicsWorld->getNumConstraints() - 1; i >= 0; i++)
    {
        btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[i];
        btRigidBody* body = btRigidBody::upcast(obj);
        if (body && body->getMotionState())
        {
            delete body->getMotionState();
        }
        m_dynamicsWorld->removeCollisionObject(obj);
        delete obj;
    }

    //delete collision shapes
    for (int j = 0; j < m_collisionShape.size(); j++)
    {
        btCollisionShape* shape = m_collisionShape[j];
        m_collisionShape[j] = nullptr;
        delete shape;
    }
}

void Core::PhysX::BulletEngine::PreUpdate(std::vector<std::shared_ptr<Core::GameObject>>& p_rigidbodies)
{
    for (auto& rigidbody : p_rigidbodies)
    {
        btTransform transform;
        rigidbody->GetComponent<Components::RigidBodyComp>()->m_rigidbody->m_rigidbody->getMotionState()->getWorldTransform(transform);
        btVector3 pos = transform.getOrigin();
        glm::vec3 position = glm::vec3(pos.getX(), pos.getY(), pos.getZ());
        rigidbody->GetComponent<Components::TransformComp>()->m_transform->SetPosition(position);
    }
}

void BulletEngine::PhysXUpdate(float p_deltaTime) const
{
    m_dynamicsWorld->stepSimulation(p_deltaTime);
}

btDiscreteDynamicsWorld* BulletEngine::GetDynamicsWorld() const
{
    return m_dynamicsWorld.get();
}

btAlignedObjectArray<btCollisionShape*> BulletEngine::GetCollisionShape() const
{
    return m_collisionShape;
}

void BulletEngine::Init()
{
    //------- START INIT -------//

    //collision configuration contains default setup for memory, collision setup
    m_collisionConfiguration = std::make_unique<btDefaultCollisionConfiguration>();
    //collisionConfiguration = new btDefaultCollisionConfiguration();

    //use default collision dispatcher
    m_dispatcher = std::make_unique<btCollisionDispatcher>(m_collisionConfiguration.get());
    //dispatcher = new btCollisionDispatcher(collisionConfiguration);

    //btDbvBroadphase is good apparently
    m_overlappingPairCache = std::make_unique<btDbvtBroadphase>();

    //default constraint solver
    m_solver = std::make_unique<btSequentialImpulseConstraintSolver>();

    m_dynamicsWorld = std::make_unique<btDiscreteDynamicsWorld>(m_dispatcher.get(),
                                                                m_overlappingPairCache.get(),
                                                                m_solver.get(),
                                                                m_collisionConfiguration.get());

    m_dynamicsWorld->setGravity(btVector3(0, -1, 0));

    //------- END INIT -------//
}

void BulletEngine::SetupRigidBodies(std::vector<std::shared_ptr<Core::GameObject>>& p_rigidbodies)
{
    for (auto& rb : p_rigidbodies)
    {
        m_collisionShape.push_back(rb->GetComponent<Components::RigidBodyComp>()->m_rigidbody->m_colShape);
        m_dynamicsWorld->addRigidBody(rb->GetComponent<Components::RigidBodyComp>()->m_rigidbody->m_rigidbody);
    }
}

void Core::PhysX::BulletEngine::LoadRigidBodies(std::vector<std::shared_ptr<Core::GameObject>>& p_gameObjects, std::vector<std::shared_ptr<Core::GameObject>>& p_rigidbodies)
{
    for (auto& p_rigid : p_gameObjects)
    {
        if (p_rigid->GetComponent<Components::RigidBodyComp>() != nullptr)
        {
            p_rigidbodies.emplace_back(p_rigid);
        }
    }
}
