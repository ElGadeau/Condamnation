#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <Rendering/Shader/Shader.h>

namespace GUI
{
    struct API_RENDERING Character
    {
        GLuint     TextureID;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        GLuint     Advance;
    };

    class API_RENDERING TextUI
    {
    public:
        TextUI();
        ~TextUI() = default;

        void LoadFont();
        void RenderText(Rendering::Shaders::Shader& p_shader,
                        const std::string&          p_text, GLfloat p_x,
                        GLfloat                     p_y,
                        GLfloat                     p_scale, glm::vec3 p_color);

    private:
        GLint                       m_VAO;
        GLint                       m_VBO;
        std::map<GLchar, Character> Characters;
    };
}
