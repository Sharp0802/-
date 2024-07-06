#include "buffer.h"

namespace tron
{
    Buffer::Buffer(BufferType type, BufferPolicy policy)
    {
    }

    void Buffer::BufferData(const void* data, const size_t size)
    {
        glBufferData(*_buffer, static_cast<GLsizeiptr>(size), data, _policy);
    }

    void Buffer::Use() const
    {
        glBindBuffer(_type, *_buffer);
    }
}
