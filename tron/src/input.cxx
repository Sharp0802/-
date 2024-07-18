#include "input.h"

namespace tron
{
    GLFW* Input::_context = nullptr;

    void Input::SetContext(GLFW* glfw)
    {
        _context = glfw;
    }

    bool Input::GetKey(int key)
    {
        return glfwGetKey(_context->GetWindow(), key) == GLFW_PRESS;
    }

    float Input::GetScroll()
    {
        return _context->Scroll;
    }

    glm::vec2 Input::GetCursor()
    {
        return _context->Cursor;
    }
}
