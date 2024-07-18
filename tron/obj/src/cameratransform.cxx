#include "cameratransform.h"

namespace tron::obj
{
    CameraTransform::CameraTransform(class GameObject* object)
        : Transform(Type<CameraTransform>::GetID(), object),
          PROP_AUTO_FIELD(Yaw)(glm::radians(90.f)),
          PROP_AUTO_FIELD(Pitch)(0),
          PROP_AUTO_FIELD(FoV)(45)
    {
    }

    CameraTransform::operator glm::mat4() const
    {
        constexpr auto up = glm::vec3(0, 1, 0);

        const auto projection = glm::perspective(
            glm::radians(FoV),
            800.0f / 600.0f,
            0.1f,
            100.0f);
        const auto view = lookAt(Position, Position + Front, up);

        return projection * view;
    }

    PROP_GETTER_DEF(CameraTransform, Front) const
    {
        glm::vec3 dir;
        dir.x = cos(Yaw) * cos(Pitch);
        dir.y = sin(Pitch);
        dir.z = sin(Yaw) * cos(Pitch);
        return normalize(dir);
    }

    void CameraTransform::Awake()
    {
    }

    void CameraTransform::Start()
    {
    }

    void CameraTransform::Update()
    {
    }

    void CameraTransform::Destroy()
    {
    }
}
