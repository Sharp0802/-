#pragma once

#include "pch.h"
#include "property.h"

namespace tron
{
    class Transform
    {
    public:
        Transform();

        [[nodiscard]]
        operator glm::mat4() const;

        PROP_AUTO(public, glm::vec3, Position);
        PROP_AUTO(public, glm::vec3, Scale);
        PROP_AUTO(public, glm::quat, Rotation);
    };
}
