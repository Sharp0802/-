#pragma once

#include "pch.h"

namespace tron
{
    class GLFW
    {
        bool        _bad;
        GLFWwindow* _window;
        int         _width;
        int         _height;

    public:
        GLFW();

        ~GLFW();

        [[nodiscard]]
        GLFWwindow* GetWindow() const;

        void Update();

        [[nodiscard]]
        std::pair<int, int> GetSize() const;

        bool operator!() const;
    };
}
