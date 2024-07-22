#pragma once

#include "buffer.h"
#include "pch.h"
#include "property.h"

namespace tron
{
    class __GLSLLight
    {
        friend class Light;
        friend class PointLight;
        friend class DirectionalLight;

        __GLSLLight(glm::vec3 direction, glm::vec3 color);

        __GLSLLight(glm::vec3 position, glm::vec3 color, float constant, float linear, float quadratic);

        __GLSLLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float cutOff, float outerCutOff);

        int32_t Mode;
        // Spotlight
        float CutOff{};
        float OuterCutOff{};
        // Point
        float Constant{};

        float Linear{};
        float Quadratic{};
        DUMMY(2 * sizeof(int)) = {};

        glm::vec3 Position{};
        DUMMY(sizeof(int)) = {};

        glm::vec3 Direction{};
        DUMMY(sizeof(int)) = {};

        glm::vec3 Color;
        DUMMY(sizeof(int)) = {};
    };

    class Light
    {
    protected:
        Light(glm::vec3 position, glm::vec3 color);

    public:
        virtual ~Light() = default;

        PROP_AUTO(public, glm::vec3, Position);
        PROP_AUTO(public, glm::vec3, Color);

        virtual void LoadOn(Buffer& buffer) = 0;
    };

    class PointLight final : public Light
    {
    public:
        PointLight(const glm::vec3& position, const glm::vec3& color);

        PROP_AUTO(public, float, AttenuationRange);

        void LoadOn(Buffer& buffer) override;
    };

    class DirectionalLight final : public Light
    {
    public:
        DirectionalLight(const glm::vec3& direction, const glm::vec3& color);

        PROP_AUTO(public, glm::vec3, Direction);
        PROP_GETTER(Position) = delete;
        PROP_SETTER(Position) = delete;

        void LoadOn(Buffer& buffer) override;
    };

    class LightArray
    {

    };
}
