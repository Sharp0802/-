#pragma once

#include "pch.h"
#include "glfw.h"

namespace tron
{
    class Input
    {
        static GLFW* _context;

    public:
        static void SetContext(GLFW* glfw);

        static bool GetKey(int key);

        static float GetScroll();

        static glm::vec2 GetCursor();
    };
}
