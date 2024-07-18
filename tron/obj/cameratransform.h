#pragma once

#include "gameobject.h"
#include "transform.h"

namespace tron::obj
{
    class CameraTransform final : public Transform
    {
    public:
        CameraTransform(class GameObject* object);

        [[nodiscard]]
        operator glm::mat4() const override;

        PROP_RO(glm::vec3, Front);
        PROP_GETTER(Front) const;

        PROP_AUTO(public, float, Yaw);
        PROP_AUTO(public, float, Pitch);
        PROP_AUTO(public, float, FoV);

        void Awake() override;

        void Start() override;

        void Update() override;

        void Destroy() override;

        /* TODO : Scale in camera is not implemented yet */
        PROP_GETTER(Scale) = delete;
        PROP_SETTER(Scale) = delete;

        /* Yaw/Pitch replaces Rotation */
        PROP_GETTER(Rotation) = delete;
        PROP_SETTER(Rotation) = delete;
    };
}
