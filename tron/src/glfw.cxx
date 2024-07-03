#include "glfw.h"

#include "log.h"

namespace
{
    void UpdateFPSCounter(GLFWwindow* window)
    {
        static double prev = glfwGetTime();
        static int cFPS;

        double current = glfwGetTime();
        double elapsed = current - prev;

        if (elapsed > 0.25)
        {
            glfwSetWindowTitle(window, std::format("{:.2f}", cFPS / elapsed).data());

            prev = current;
            cFPS = 0;
        }

        cFPS++;
    }
}


namespace tron
{
    GLFW::GLFW()
    {
        glfwSetErrorCallback([] (int code, const char* desc) {
            perr("GLFW ({}): {}", code, desc);
        });

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

        glfwSetWindowUserPointer(_window, this);
        glfwSetWindowSizeCallback(_window, [](GLFWwindow* window, const int width, const int height)
        {
            const auto this_ = static_cast<GLFW*>(glfwGetWindowUserPointer(window));
            this_->_width  = width;
            this_->_height = height;
        });

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

    void GLFW::Update()
    {
        glfwSwapBuffers(_window);
        glfwPollEvents();

        UpdateFPSCounter(_window);

        auto [width, height] = GetSize();
        glViewport(0, 0, width, height);
    }

    std::pair<int, int> GLFW::GetSize() const
    {
        return std::make_pair(_width, _height);
    }

    bool GLFW::operator!() const
    {
        return _bad;
    }
}
