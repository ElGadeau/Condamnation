#include "stdafx.h"
#include <Rendering/GUI/TextUI.h>
#include <iostream>

GUI::TextUI::TextUI()
{
    LoadFont();
}

void GUI::TextUI::LoadFont()
{
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: could not init freetype library\n";

    // FT_Face face;
    if (FT_New_Face(ft, R"(..\Resources\Font\Doom.ttf)", 0, &m_face))
        std::cout << "ERROR::FREETYPRE: failed to load font\n";

    FT_Set_Pixel_Sizes(m_face, 0, 48);

    // if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    //     std::cout << "ERROR::FREETYPE: failed to load Glyph\n";

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (GLubyte c = 0; c < 128; c++)
    {
        //load character Glyph
        if (FT_Load_Char(m_face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYPE: failed to load Glyph\n";
            continue;
        }

        //generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                     GL_TEXTURE_2D,
                     0,
                     GL_RED,
                     m_face->glyph->bitmap.width,
                     m_face->glyph->bitmap.rows,
                     0,
                     GL_RED,
                     GL_UNSIGNED_BYTE,
                     m_face->glyph->bitmap.buffer
                    );

        //set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        //now store the texture for later use
        Character character = {
        texture,
        glm::ivec2(m_face->glyph->bitmap.width, m_face->glyph->bitmap.rows),
        glm::ivec2(m_face->glyph->bitmap_left, m_face->glyph->bitmap_top),
        m_face->glyph->advance.x
        };

        Characters.insert(std::pair<GLchar, Character>(c, character));
    }

    FT_Done_Face(m_face);
    FT_Done_FreeType(ft);

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GUI::TextUI::RenderText(Rendering::Shaders::Shader& p_shader,
                             const std::string&          p_text, GLfloat p_x,
                             GLfloat                     p_y,
                             GLfloat                     p_scale,
                             glm::vec3                   p_color)
{
    p_shader.ApplyShader();
    glUniform3f(glGetUniformLocation(p_shader.shaderProgram, "textColor"), p_color.x,
                p_color.y, p_color.z);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

    //iteration through all characters
    std::string::const_iterator c;
    for (c = p_text.begin(); c != p_text.end(); ++c)
    {
        Character ch = Characters[*c];

        GLfloat xPos = p_x + ch.Bearing.x * p_scale;
        GLfloat yPos = p_y - (ch.Size.y - ch.Bearing.y) * p_scale;

        GLfloat w = ch.Size.x * p_scale;
        GLfloat h = ch.Size.y * p_scale;

        //update vbo for each character
        GLfloat vertices[6][4] = {
            {xPos, yPos + h, 0.0, 0.0},
            {xPos, yPos, 0.0, 1.0},
            {xPos + w, yPos, 1.0, 1.0},

            {xPos, yPos + h, 0.0, 0.0},
            {xPos + w, yPos, 1.0, 1.0},
            {xPos + w, yPos + h, 1.0, 0.0}
        };

        //render glyph texture
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        
        //update content of vbo
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        //render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        p_x += (ch.Advance >> 6) * p_scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
