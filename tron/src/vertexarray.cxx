#include "vertexarray.h"

namespace
{
    std::shared_ptr<GLuint> CreateVertexArray()
    {
        auto vertexarray = new GLuint;
        glGenVertexArrays(1, vertexarray);
        return { vertexarray, [](const GLuint* p) { glDeleteVertexArrays(1, p); } };
    }
}

namespace tron
{
    VertexArray::VertexArray() : _array(CreateVertexArray())
    {
    }

    void VertexArray::Use() const
    {
        glBindVertexArray(*_array);
    }
}
