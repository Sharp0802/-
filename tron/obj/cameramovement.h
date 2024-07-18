#pragma once

#include "pch.h"
#include "gameobject.h"
#include "cameratransform.h"
#include "input.h"
#include "log.h"
#include "ttime.h"

namespace tron::obj
{
    class CameraMovement final : public Component
    {
        CameraTransform* _cameraTransform = nullptr;

    public:
        CameraMovement(tron::GameObject* object) : Component(Type<CameraMovement>::GetID(), object)
        {
        }

        void Awake() override
        {
            _cameraTransform = GameObject->GetComponent<CameraTransform>();
            if (!_cameraTransform)
                perr("there is no `CameraTransform` component");
        }

        void Start() override
        {
        }

        void Update() override
        {
            /* View direction */
            static auto lastCursor = Input::GetCursor();
            auto cursorOffset = Input::GetCursor() - lastCursor;
            lastCursor = Input::GetCursor();

            constexpr float sensitivity = 0.1f;
            cursorOffset *= sensitivity * Time::GetDelta();

            _cameraTransform->Yaw += cursorOffset.x;
            _cameraTransform->Pitch += cursorOffset.y;

            if (_cameraTransform->Pitch > glm::radians(85.f))
                _cameraTransform->Pitch = glm::radians(85.f);
            else if (_cameraTransform->Pitch < -glm::radians(85.f))
                _cameraTransform->Pitch = -glm::radians(85.f);

            /* Zoom */
            _cameraTransform->FoV -= Input::GetScroll();
            if (_cameraTransform->FoV < 1)
                _cameraTransform->FoV = 1;
            else if (_cameraTransform->FoV > 75)
                _cameraTransform->FoV = 75;

            /* Movement */
            constexpr auto up = glm::vec3(0, 1, 0);

            constexpr auto speed = 1.f;

            if (Input::GetKey(GLFW_KEY_W))
                _cameraTransform->Position += _cameraTransform->Front * Time::GetDelta() * speed;
            if (Input::GetKey(GLFW_KEY_S))
                _cameraTransform->Position -= _cameraTransform->Front * Time::GetDelta() * speed;
            if (Input::GetKey(GLFW_KEY_A))
                _cameraTransform->Position -= normalize(cross(_cameraTransform->Front, up)) * Time::GetDelta() * speed;
            if (Input::GetKey(GLFW_KEY_D))
                _cameraTransform->Position += normalize(cross(_cameraTransform->Front, up)) * Time::GetDelta() * speed;

            if (Input::GetKey(GLFW_KEY_SPACE))
                _cameraTransform->Position += glm::vec3(0, 1, 0) * Time::GetDelta() * speed;
            if (Input::GetKey(GLFW_KEY_LEFT_SHIFT))
                _cameraTransform->Position += glm::vec3(0, -1, 0) * Time::GetDelta() * speed;
        }

        void Destroy() override
        {
        }
    };
}
