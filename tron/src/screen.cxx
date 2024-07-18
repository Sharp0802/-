#include "screen.h"

namespace tron
{
    GLFW* Screen::_context;

    void Screen::SetContext(GLFW* context)
    {
        _context = context;
    }

    glm::vec<2, int> Screen::GetSize()
    {
        int width, height;
        glfwGetWindowSize(_context->GetWindow(), &width, &height);
        return { width, height };
    }
}
