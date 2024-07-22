#include "light.h"

namespace tron
{
    __GLSLLight::__GLSLLight(glm::vec3 direction, glm::vec3 color)
        : Mode(0),
          Direction(direction),
          Color(color)
    {
    }

    __GLSLLight::__GLSLLight(glm::vec3 position, glm::vec3 color, float constant, float linear, float quadratic)
        : Mode(1),
          Constant(constant),
          Linear(linear),
          Quadratic(quadratic),
          Position(position),
          Color(color)
    {
    }

    __GLSLLight::__GLSLLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, float cutOff, float outerCutOff)
        : Mode(2),
          CutOff(cutOff),
          OuterCutOff(outerCutOff),
          Position(position),
          Direction(direction),
          Color(color)
    {
    }

    Light::Light(glm::vec3 position, glm::vec3 color)
        : PROP_AUTO_FIELD(Position)(position),
          PROP_AUTO_FIELD(Color)(color)
    {
    }

    PointLight::PointLight(const glm::vec3& position, const glm::vec3& color)
        : Light(position, color),
          PROP_AUTO_FIELD(AttenuationRange)(0)
    {
    }

    void PointLight::LoadOn(Buffer& buffer)
    {
        auto constant  = fabsf(AttenuationRange) > 0.0001f;
        auto linear    = 4.5f / AttenuationRange;
        auto quadratic = 13.f / glm::pow(AttenuationRange - 7, 1.63f);

        __GLSLLight light(Position, Color, constant, linear, quadratic);
        buffer.BufferData(&light, sizeof light);
    }

    DirectionalLight::DirectionalLight(const glm::vec3& direction, const glm::vec3& color)
        : Light({}, color),
          PROP_AUTO_FIELD(Direction)(direction)
    {
    }

    void DirectionalLight::LoadOn(Buffer& buffer)
    {
        const __GLSLLight light(Direction, Color);
        buffer.BufferData(&light, sizeof light);
    }
}
