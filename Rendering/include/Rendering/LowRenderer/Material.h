#pragma once
#include <Rendering/Export.h>

namespace Rendering::LowRenderer
{
    class API_RENDERING Material
    {
    public:

        Material() { shininess = 0.5f; r = 1; g = 1; b = 1; };
        ~Material() {};

        void SetColor(float red, float blue, float green) { r = red; g = blue; b = blue; };
        void SetShininess(float shine) { shininess = shine; };
        float shininess;
        
        float r;
        float g;
        float b;
    };
}
