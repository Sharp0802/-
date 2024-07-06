#pragma once

#include "pch.h"

namespace tron
{
    enum BufferType
    {
        BT_Array        = GL_ARRAY_BUFFER,
        BT_ElementArray = GL_ELEMENT_ARRAY_BUFFER
    };

    enum BufferPolicy
    {
        BP_Dynamic = GL_DYNAMIC_DRAW,
        BP_Static  = GL_STATIC_DRAW,
        BP_Stream  = GL_STREAM_DRAW,

        BP_Draw = 0,
        BP_Read = 1,
        BP_Copy = 2
    };

    class Buffer
    {
        BufferType _type;
        BufferPolicy _policy;
        std::shared_ptr<GLuint> _buffer;

    public:
        Buffer(BufferType type, std::underlying_type_t<BufferPolicy> policy);

        void BufferData(const void* data, size_t size);

        void Use() const;
    };
}
