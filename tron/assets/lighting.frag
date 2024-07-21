#version 400 core

struct Material
{
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
    float Shininess;
};

in vec3 Normal;
in vec3 FragPosition;

out vec4 Color;

uniform vec3 fLightColor;
uniform vec3 fLightPosition;
uniform vec3 fViewPosition;
uniform Material fMaterial;

void main()
{
    // Ambient
    vec3 ambient = fLightColor * fMaterial.Ambient;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(fLightPosition - FragPosition);
    float diff = max(dot(norm, lightDir), 0);
    vec3 diffuse = fLightColor * (diff * fMaterial.Diffuse);

    // Specular
    vec3 viewDir = normalize(fViewPosition - FragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0), fMaterial.Shininess);
    vec3 specular = fLightColor * (spec * fMaterial.Specular);

    vec3 result = ambient + diffuse + specular;
    Color = vec4(result, 1);
}
