#pragma once
#include "transform.h"

namespace tron
{
    class CameraTransform
    {
    public:
        CameraTransform();

        PROP_RO(glm::vec3, Front);
        PROP_GETTER(Front);

        PROP_AUTO(public, float, Yaw);
        PROP_AUTO(public, float, Pitch);
    };
}
