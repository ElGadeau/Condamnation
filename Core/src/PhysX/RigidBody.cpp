#include <PhysX/RigidBody.h>
#include <PhysX/BulletEngine.h>


void Core::PhysX::RigidBody::CreateBoxRigidBody(btVector3 p_size,
    btScalar* p_transform, float p_mass)
{
    m_colShape = new btBoxShape(p_size);
    m_colShape->setLocalScaling({ 1, 1, 1 });
    btTransform startTransform;
    startTransform.setFromOpenGLMatrix(p_transform);

    btScalar mass(p_mass);

    bool isDynamic = (mass != 0.0f);

    btVector3 localInertia(0, 0, 0);
    if (isDynamic)
        m_colShape->calculateLocalInertia(mass, localInertia);


    const auto myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, m_colShape, localInertia);
    rbInfo.m_restitution = 0.4f;
    m_rigidbody = new btRigidBody(rbInfo);
}

void Core::PhysX::RigidBody::CreateSphereRigidBody(btScalar p_radius, btScalar* p_transform, float p_mass)
{
    m_colShape = new btSphereShape(p_radius);

    btTransform startTransform;
    startTransform.setFromOpenGLMatrix(p_transform);

    const btScalar mass(p_mass);

    btVector3 localInertia(0, 0, 0);
    if (mass != 0.0f)
        m_colShape->calculateLocalInertia(mass, localInertia);


    const auto myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, m_colShape, localInertia);
    rbInfo.m_restitution = 1.0f;
    m_rigidbody = new btRigidBody(rbInfo);
}

void Core::PhysX::RigidBody::CreateCapsuleRigidBody(btScalar p_radius, btScalar p_height, btVector3 p_origin, float p_mass)
{
    m_colShape = new btCapsuleShape(p_radius, p_height);

    btTransform startTransform;
    startTransform.setIdentity();
    startTransform.setOrigin(p_origin);

    const btScalar mass(p_mass);

    btVector3 localInertia(0, 0, 0);
    if (mass != 0.0f)
        m_colShape->calculateLocalInertia(mass, localInertia);

    const auto myMotionState = new btDefaultMotionState(startTransform);
    const btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, m_colShape, localInertia);
    m_rigidbody = new btRigidBody(rbInfo);
}