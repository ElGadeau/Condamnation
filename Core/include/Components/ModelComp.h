#pragma once

#include <Rendering/Resources/Model.h>
#include <Components/Component.h>

namespace Components
{
    class ModelComp : public Component
    {
    public:
        ModelComp() : m_model {std::make_shared<Rendering::Resources::Model>()} {}
		~ModelComp() = default;

		[[nodiscard]] std::shared_ptr<Rendering::Resources::Model> GetModel() const noexcept { return m_model; }

    private:
        std::shared_ptr<Rendering::Resources::Model> m_model;
    };
}