#include <Components/EnnemieComp.h>
#include "Components/TransformComp.h"

void Components::EnnemieComp::Update()
{
    if (m_target != nullptr)
    {
        MoveToTarget();
    }
}

void Components::EnnemieComp::MoveToTarget() const
{
    glm::vec3 newPos = m_target->GetComponent<TransformComp>()->GetTransform()->
                                 GetPosition();
    normalize(newPos);
    newPos *= m_speed;

    m_gameObject.GetComponent<Components::TransformComp>()->GetTransform()->Translate(newPos);
}
