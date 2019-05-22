#pragma once

#include <Rendering/Resources/Model.h>
#include <Components/Component.h>

namespace Components
{
    class ModelComp : public Component
    {
    public:
        ModelComp();
        ~ModelComp() { delete m_model; };
        Rendering::Resources::Model* m_model;
    };
}