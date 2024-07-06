#pragma once

#include "gltype.h"
#include "log.h"
#include "pch.h"

namespace tron
{
    class VertexArray
    {
        std::shared_ptr<GLuint> _array;

    public:
        VertexArray();

        void Use() const;

        template<typename... T>
        void Register()
        {
            constexpr size_t stride = (sizeof(T) + ...);

            Use();

            size_t index = 0;
            size_t padding = 0;
            ([&]
            {
                glVertexAttribPointer(
                    index,
                    GLType<T>::Count,
                    GLType<T>::TypeEnum,
                    GL_FALSE,
                    stride,
                    reinterpret_cast<void*>(padding));
                glEnableVertexAttribArray(index);

                padding += GLType<T>::Size;
                index++;
            }(), ...);
        }
    };
}
