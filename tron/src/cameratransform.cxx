#include "cameratransform.h"

namespace tron
{
    CameraTransform::CameraTransform()
        : PROP_AUTO_FIELD(Yaw)(0),
          PROP_AUTO_FIELD(Pitch)(0)
    {
    }

    PROP_GETTER_DEF(CameraTransform, Front)
    {
        glm::vec3 dir;
        dir.x = cos(Yaw) * cos(Pitch);
        dir.y = sin(Pitch);
        dir.z = sin(Yaw) * cos(Pitch);
        return normalize(dir);
    }
}
