#version 400 core

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vColor;
layout (location = 2) in vec2 vTexCoord;

out vec3 Color;
out vec2 TexCoord;

uniform mat4 vTransform;

void main()
{
    gl_Position = vTransform * vec4(vPosition, 1.0);
    Color = vColor;
    TexCoord = vTexCoord;
}
