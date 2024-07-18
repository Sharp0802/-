#pragma once

#include "pch.h"
#include "property.h"

namespace tron
{
    class GLFW
    {
        bool        _bad;
        GLFWwindow* _window;
        int         _width;
        int         _height;
        float       _cursorX;
        float       _cursorY;
        float       _scroll;

    public:
        using WindowSize = glm::vec<2, int>;
        using CursorPos  = glm::vec2;

        GLFW();

        ~GLFW();

        [[nodiscard]]
        GLFWwindow* GetWindow() const;

        void Update();

        PROP_RO(WindowSize, Size);
        PROP_GETTER(Size);

        PROP_RO(CursorPos, Cursor);
        PROP_GETTER(Cursor);

        PROP_RO(float, Scroll);
        PROP_GETTER(Scroll);

        bool operator!() const;
    };
}
