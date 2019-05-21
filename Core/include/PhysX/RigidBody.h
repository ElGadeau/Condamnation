#pragma once
#include <bullet/btBulletDynamicsCommon.h>
#include "BulletEngine.h"

namespace Core::PhysX
{
    class RigidBody
    {
    public:
        RigidBody() {};

        btCollisionShape* m_colShape;
        btRigidBody* m_rigidbody;

        void CreateBoxRigidBody(btVector3 p_size, btScalar* p_transform, float p_mass);
        void CreateSphereRigidBody(btScalar p_radius, btScalar* p_transform, float p_mass);
        void CreateCapsuleRigidBody(btScalar p_radius, btScalar p_height, btVector3 p_origin, float p_mass);
    };
}
