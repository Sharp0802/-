#pragma once

#include "pch.h"
#include "property.h"
#include "gameobject.h"

namespace tron::obj
{
    class Transform : public Component
    {
    protected:
        Transform(size_t type, class GameObject* object);

    public:
        Transform(class GameObject* object);

        ~Transform() override = default;

        [[nodiscard]]
        virtual operator glm::mat4() const;

        PROP_AUTO(public, glm::vec3, Position);
        PROP_AUTO(public, glm::vec3, Scale);
        PROP_AUTO(public, glm::quat, Rotation)

        void Awake() override;

        void Start() override;

        void Update() override;

        void Destroy() override;
    };
}
