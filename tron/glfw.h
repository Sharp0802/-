#pragma once

#include "pch.h"

namespace tron
{
    class GLFW
    {
        bool        _bad;
        GLFWwindow* _window;

    public:
        GLFW();

        ~GLFW();

        [[nodiscard]]
        GLFWwindow* GetWindow() const;

        bool operator!() const;
    };
}
