#pragma once

#include "pch.h"
#include "gameobject.h"
#include "cameratransform.h"

namespace tron::obj
{
    class CameraMovement final : public Component
    {
        CameraTransform* _cameraTransform = nullptr;

    public:
        CameraMovement(tron::GameObject* object);

        void Awake() override;

        void Start() override;

        void Update() override;

        void Destroy() override;
    };
}
