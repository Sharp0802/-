#version 400 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 Normal;
out vec3 FragPosition;

uniform mat4 vProjectionView;
uniform mat4 vModel;

void main()
{
    gl_Position = vProjectionView * vModel * vec4(position, 1);
    FragPosition = vec3(vModel * vec4(position, 1));
    Normal = mat3(transpose(inverse(vModel))) * normal;
}
