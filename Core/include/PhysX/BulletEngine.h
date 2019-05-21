#pragma once
#include <memory>
#include <vector>

#include <Core/GameObject.h>
#include <bullet/btBulletDynamicsCommon.h>

namespace Core::PhysX
{
    class BulletEngine
    {
    public:
        BulletEngine();
        ~BulletEngine();

        void PreUpdate(std::vector<std::shared_ptr<Core::GameObject>>& p_rigidbodies);
        void PhysXUpdate(float p_deltaTime) const;
        void SetupRigidBodies(std::vector<std::shared_ptr<Core::GameObject>>& p_rigidbodies);
        void LoadRigidBodies(std::vector<std::shared_ptr<Core::GameObject>>& p_gameObjects, std::vector<std::shared_ptr<Core::GameObject>>& p_rigidbodies);
        btDiscreteDynamicsWorld* GetDynamicsWorld() const;
        btAlignedObjectArray<btCollisionShape*> GetCollisionShape() const;

    private:
        void Init();

        std::unique_ptr<btDefaultCollisionConfiguration> m_collisionConfiguration;
        std::unique_ptr<btCollisionDispatcher> m_dispatcher;
        std::unique_ptr<btBroadphaseInterface> m_overlappingPairCache;
        std::unique_ptr<btSequentialImpulseConstraintSolver> m_solver;
        std::unique_ptr<btDiscreteDynamicsWorld> m_dynamicsWorld;

        btAlignedObjectArray<btCollisionShape*> m_collisionShape;
    };
}
