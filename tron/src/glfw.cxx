#include "glfw.h"

namespace tron
{
    GLFW::GLFW()
    {
        if (!glfwInit())
        {
            std::println(std::cerr, "couldn't start GLFW3");
            _bad = true;
            return;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        _window = glfwCreateWindow(640, 480, "Hello Triangle", nullptr, nullptr);
        if (!_window)
        {
            std::println(std::cerr, "couldn't open window");
            _bad = true;
            return;
        }
        glfwMakeContextCurrent(_window);

        _bad = false;
    }

    GLFW::~GLFW()
    {
        glfwTerminate();
    }

    GLFWwindow* GLFW::GetWindow() const
    {
        return _window;
    }

    bool GLFW::operator!() const
    {
        return _bad;
    }
}
