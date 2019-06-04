#include <GUI/TextUI.h>
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

    FT_Face face;
    if (FT_New_Face(ft, R"(..\Resources\Font\Doom.ttf)", 0, &face))
        std::cout << "ERROR::FREETYPRE: failed to load font\n";

    FT_Set_Pixel_Sizes(face, 0, 48);

    if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
        std::cout << "ERROR::FREETYPE: failed to load Glyph\n";

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (GLubyte c = 0; c < 128; c++)
    {
        //load character Glyph
        if (FT_Load_Char())


    }
}
