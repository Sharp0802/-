#include "buffer.h"

namespace
{
    std::shared_ptr<GLuint> CreateBuffer()
    {
        auto buffer = new GLuint;
        glCreateBuffers(1, buffer);
        return { buffer, [](const GLuint* p) { glDeleteBuffers(1, p); } };
    }
}

namespace tron
{
    Buffer::Buffer(const BufferType type, const std::underlying_type_t<BufferPolicy> policy)
        : _type(type),
          _policy(static_cast<BufferPolicy>(policy)),
          _buffer(CreateBuffer())
    {
    }

    void Buffer::BufferData(const void* data, const size_t size)
    {
        Use();
        glBufferData(_type, static_cast<GLsizeiptr>(size), data, _policy);
    }

    void Buffer::Use() const
    {
        glBindBuffer(_type, *_buffer);
    }
}
