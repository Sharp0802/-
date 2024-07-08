#pragma once

#include "gltype.h"
#include "log.h"
#include "pch.h"

namespace tron
{
    class VertexArray
    {
        std::shared_ptr<GLuint> _array;

        VertexArray();

    public:
        void Use() const;

        template<typename... T>
        static VertexArray Create()
        {
            constexpr size_t stride = (sizeof(T) + ...);

            VertexArray vao;
            vao.Use();

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

            return vao;
        }
    };
}