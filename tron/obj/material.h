#pragma once

#include "buffer.h"
#include "pch.h"
#include "property.h"

namespace tron
{
    class __GLSLMaterial
    {
        friend class Material;

        __GLSLMaterial(
            float shininess,
            glm::vec3 ambient,
            glm::vec3 diffuse,
            glm::vec3 specular);

        float     Shininess;
        DUMMY(3 * sizeof(int)) = {};
        glm::vec3 Ambient;
        DUMMY(sizeof(int)) = {};
        glm::vec3 Diffuse;
        DUMMY(sizeof(int)) = {};
        glm::vec3 Specular;
        DUMMY(sizeof(int)) = {};
    };

    class Material
    {
    public:
        Material(
            float shininess,
            glm::vec3 ambient,
            glm::vec3 diffuse,
            glm::vec3 specular);

        PROP_AUTO(public, float, Shininess);
        PROP_AUTO(public, glm::vec3, Ambient);
        PROP_AUTO(public, glm::vec3, Diffuse);
        PROP_AUTO(public, glm::vec3, Specular);

        void LoadOn(Buffer& buffer);
    };
}
