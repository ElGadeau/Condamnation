#version 450 core

layout (location = 0) in vec4 vertex;
out vec2 TextCoords;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(vertex.x, vertex.y, 0.0, 1.0);
    TextCoords = vec2(vertex.z, vertex.w);
}