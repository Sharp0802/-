#include "glew.h"

#include "log.h"

namespace tron
{
    GLEW::GLEW()
    {
        glewExperimental = GL_TRUE;
        glewInit();

        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* version = glGetString(GL_VERSION);

        pout(
            "\nRenderer: {}\nVersion : {}",
            std::string(reinterpret_cast<const char*>(renderer)),
            std::string(reinterpret_cast<const char*>(version)));
    }
}
