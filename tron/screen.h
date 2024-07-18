#pragma once

#include "glfw.h"

namespace tron
{
    class Screen
    {
        static GLFW* _context;

    public:
        static void SetContext(GLFW* context);

        static glm::vec<2, int> GetSize();
    };
}
