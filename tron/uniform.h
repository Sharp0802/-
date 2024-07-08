#pragma once

#include "gltype.h"

#define BEGIN_UNIFORM  GLint _loc; explicit Uniform(GLint loc) : _loc(loc) { }

namespace tron
{
    template<typename T>
    void glUniform(GLint loc, T value);

#define TRON_GL_UNIFORM(type, f, ...) template<> inline void glUniform<type>(GLint loc, type v) { f(loc, __VA_ARGS__); }

    TRON_GL_UNIFORM(int, glUniform1i, v);
    TRON_GL_UNIFORM(unsigned int, glUniform1ui, v);
    TRON_GL_UNIFORM(float, glUniform1f, v);

    TRON_GL_UNIFORM(glm::vec2, glUniform2f, v.x, v.y);
    TRON_GL_UNIFORM(glm::vec3, glUniform3f, v.x, v.y, v.z);
    TRON_GL_UNIFORM(glm::vec4, glUniform4f, v.x, v.y, v.z, v.w);

#define TRON_GL_UNIFORM_MATRIX(c, r) TRON_GL_UNIFORM(glm::mat##c##x##r, glUniformMatrix2fv, 1, GL_FALSE, glm::value_ptr(v))

    TRON_GL_UNIFORM_MATRIX(2, 2)
    TRON_GL_UNIFORM_MATRIX(2, 3)
    TRON_GL_UNIFORM_MATRIX(2, 4)
    TRON_GL_UNIFORM_MATRIX(3, 3)
    TRON_GL_UNIFORM_MATRIX(3, 4)
    TRON_GL_UNIFORM_MATRIX(4, 4)

#undef TRON_GL_UNIFORM_MATRIX
#undef TRON_GL_UNIFORM

    template<typename T>
    struct Uniform
    {
        GLint _loc;

        explicit Uniform(const GLint loc) : _loc(loc)
        {
        }

        Uniform& operator=(T value)
        {
            glUniform<T>(_loc, value);
            return *this;
        }
    };
}
