#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace GUI
{
    struct Character
    {
        GLuint TextureID;
        glm::ivec2 Size;
        glm::ivec2 Bearing;
        GLuint Advance;
    };

    class TextUI
    {
    public:
        TextUI();
        ~TextUI() = default;

        void LoadFont();


        std::map<GLchar, Character> Characters;
    };
}
