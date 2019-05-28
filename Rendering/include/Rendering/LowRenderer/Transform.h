#pragma once
#include <Rendering/Export.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Rendering::LowRenderer
{
    class API_RENDERING Transform
    {
    public:
		Transform();
		~Transform();
		
        void Translate(const glm::vec3& p_translation);
        void Rotate(const glm::vec3& p_rotation);
        void Scale(const glm::vec3& p_scaling);
        void SetPosition(const glm::vec3 & p_pos);

        const glm::vec3& GetPosition() const noexcept { return m_pos; };
        const glm::vec3& GetRotation() const noexcept { return m_rot; };
        const glm::vec3& GetScale() const noexcept { return m_scale; };
        glm::mat4 m_transMat;

    private:
        glm::vec3 m_pos;
        glm::vec3 m_rot;
        glm::vec3 m_scale;
    };
}