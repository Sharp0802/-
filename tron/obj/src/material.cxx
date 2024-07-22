#include "material.h"

namespace tron
{
    __GLSLMaterial::__GLSLMaterial(float shininess, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
        : Shininess(shininess),
          Ambient(ambient),
          Diffuse(diffuse),
          Specular(specular)
    {
    }

    Material::Material(float shininess, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
        : PROP_AUTO_FIELD(Shininess)(shininess),
          PROP_AUTO_FIELD(Ambient)(ambient),
          PROP_AUTO_FIELD(Diffuse)(diffuse),
          PROP_AUTO_FIELD(Specular)(specular)
    {
    }

    void Material::LoadOn(Buffer& buffer)
    {
        const __GLSLMaterial material(Shininess, Ambient, Diffuse, Specular);
        buffer.BufferData(&material, sizeof material);
    }
}
