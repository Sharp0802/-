#pragma once

#include "pch.h"
#include "log.h"
#include "uniform.h"

namespace tron
{
    enum ShaderType : GLenum
    {
        ST_Fragment = GL_FRAGMENT_SHADER,
        ST_Vertex   = GL_VERTEX_SHADER
    };

    class Shader
    {
        friend class Program;

        std::shared_ptr<GLuint> _shader;
        ShaderType              _type;
        bool                    _bad = false;

    public:
        Shader(const std::string& path, ShaderType type);

        [[nodiscard]]
        bool operator!() const;
    };

    class Program
    {
        std::shared_ptr<GLuint> _program;
        bool                    _bad = false;

    public:
        explicit Program(const std::vector<Shader>& shaders);

        Program(std::initializer_list<Shader> shaders);

        [[nodiscard]]
        bool operator!() const;

        void Use() const;

        template<typename T>
        [[nodiscard]]
        Uniform<T> GetUniform(const std::string& name) const
        {
            return Uniform<T>(glGetUniformLocation(*_program, name.data()));
        }
    };
}
