#version 400 core

out vec4 fColor;

in vec3 Color;
in vec2 TexCoord;

uniform sampler2D fTexture;

void main()
{
  fColor = texture(fTexture, TexCoord) * vec4(Color, 1);
}
