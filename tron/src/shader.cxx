#include "shader.h"

#include "global.h"
#include "log.h"

namespace
{
    std::shared_ptr<GLuint> CreateShader(const tron::ShaderType type)
    {
        auto p = new GLuint;
        *p     = glCreateShader(type);
        return { p, [](const GLuint* e) { glDeleteShader(*e); } };
    }

    std::shared_ptr<GLuint> CreateProgram()
    {
        auto p = new GLuint;
        *p     = glCreateProgram();
        return { p, [](const GLuint* e) { glDeleteProgram(*e); } };
    }
}

namespace tron
{
    Shader::Shader(
        const std::string& path,
        const ShaderType   type)
        : _shader(CreateShader(type)), _type(type)
    {
        auto fullname = Global::GetPath(path);

        std::ifstream ifs;
        ifs.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        try
        {
            ifs.open(fullname, std::ios_base::in | std::ios_base::binary);
        }
        catch (std::ios_base::failure& e)
        {
            perr("[{}] while reading '{}': {}", *_shader, fullname, e.what());
            _bad = true;
            return;
        }

        auto fsize = ifs.tellg();
        ifs.seekg(0, std::ios::end);
        fsize = ifs.tellg() - fsize;
        ifs.seekg(0, std::ios::beg);

        std::vector<char> buffer(fsize);
        ifs.read(buffer.data(), static_cast<size_t>(fsize) - 1 /* why? */);

        const char* pbuffer = buffer.data();
        glShaderSource(*_shader, 1, &pbuffer, nullptr);
        glCompileShader(*_shader);


        GLint params = -1;
        glGetShaderiv(*_shader, GL_COMPILE_STATUS, &params);
        if (params != GL_TRUE)
        {
            thread_local char log[BUFSIZ] = {};
            GLsizei           size        = BUFSIZ;
            glGetShaderInfoLog(*_shader, size, &size, log);

            perr("[{}] Couldn't compile GL shader\n{}", *_shader, static_cast<char*>(log));
            _bad = true;
            return;
        }
    }

    bool Shader::operator!() const
    {
        return _bad;
    }

    Program::Program(const std::vector<Shader>& shaders) : _program(CreateProgram())
    {
        for (const auto& shader: shaders)
        {
            if (!shader)
            {
                perr("[{}] cannot be linked with bad shader({})", *_program, *shader._shader);
                _bad = true;
                continue;
            }

            glAttachShader(*_program, *shader._shader);
        }
        if (_bad)
            return;

        glLinkProgram(*_program);

        GLint params = -1;
        glGetProgramiv(*_program, GL_LINK_STATUS, &params);
        if (params != GL_TRUE)
        {
            thread_local char log[BUFSIZ] = {};
            GLsizei           size        = BUFSIZ;
            glGetProgramInfoLog(*_program, size, &size, static_cast<char*>(log));

            perr("[{}] Couldn't link GL program\n{}", *_program, log);
            _bad = true;
        }
    }

    Program::Program(const std::initializer_list<Shader> shaders): Program(static_cast<std::vector<Shader>>(shaders))
    {
    }

    bool Program::operator!() const
    {
        return _bad;
    }

    void Program::Use() const
    {
        glUseProgram(*_program);
    }
}
