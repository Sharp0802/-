#version 460 core

const int LIGHT_DIRECTIONAL = 0;
const int LIGHT_POINT = 1;
const int LIGHT_SPOTLIGHT = 2;

struct Light
{
    int Mode;

    // Spotlight
    float CutOff;
    float OuterCutOff;

    // Point
    float Constant;
    float Linear;
    float Quadratic;

    vec3 Position;
    vec3 Direction;
    vec3 Color;
};


in vec3 Normal;
in vec3 FragPosition;

out vec4 Color;

uniform vec3 fViewPosition;

layout (std430, binding = 1) buffer Material
{
    float Shininess;
    vec3 Ambient;
    vec3 Diffuse;
    vec3 Specular;
} fMaterial;

uniform int fLightCount;

layout (std430, binding = 2) buffer LightArray
{
    Light fLights[];
};

vec3 CalculateLight(Light light)
{
    if (light.Mode != LIGHT_DIRECTIONAL)
        light.Direction = -(light.Position - FragPosition);

    // Ambient
    vec3 ambient = light.Color * fMaterial.Ambient;

    // Diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-light.Direction);
    float diff = max(dot(norm, lightDir), 0);
    vec3 diffuse = light.Color * (diff * fMaterial.Diffuse);

    // Specular
    vec3 viewDir = normalize(fViewPosition - FragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0), fMaterial.Shininess);
    vec3 specular = light.Color * (spec * fMaterial.Specular);

    if (light.Mode == LIGHT_POINT && light.Constant > 0)
    {
        float dist = length(light.Position - FragPosition);
        float attenuation = 1 / (light.Constant + light.Linear * dist + light.Quadratic * (dist * dist));

        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;
    }

    if (light.Mode == LIGHT_SPOTLIGHT)
    {
        float theta = dot(lightDir, normalize(-light.Direction));
        float epsilon = light.CutOff - light.OuterCutOff;
        float intensity = clamp((theta - light.OuterCutOff) / epsilon, 0, 1);

        if (theta < light.CutOff)
            return ambient;

        diffuse *= intensity;
        specular *= intensity;
    }

    return ambient + diffuse + specular;
}

void main()
{
    vec3 result = vec3(0);
    for (int i = 0; i < fLightCount; ++i)
        result += CalculateLight(fLights[i]);
    Color = vec4(result, 1);
}
