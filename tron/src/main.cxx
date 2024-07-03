#include "pch.h"
#include "glew.h"
#include "glfw.h"
#include "log.h"


int main(int, char* argv[])
{
    tron::Global::Path = std::filesystem::path(argv[0]).parent_path();

    tron::GLFW glfw;
    if (!glfw)
        return 1;

    tron::GLEW glew;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    float points[] = {
         .0,  .5, .0,
         .5, -.5, .0,
        -.5, -.5, .0
    };

    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof points, points, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    const char* vsha =
"#version 400\n"
"layout(location = 0) in vec3 vp;"
"void main() {"
"  gl_Position = vec4(vp, 1.0);"
"}";

    const char* fsha =
"#version 400\n"
"out vec4 frag_colour;"
"void main() {"
"  frag_colour = vec4(0.5, 0.0, 0.5, 1.0);"
"}";

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vsha, nullptr);
    glCompileShader(vs);

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fsha, nullptr);
    glCompileShader(fs);

    GLuint program = glCreateProgram();
    glAttachShader(program, fs);
    glAttachShader(program, vs);
    glLinkProgram(program);

    while (!glfwWindowShouldClose(glfw.GetWindow()))
    {
        glfw.Update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, .3, .7, 1);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    return 0;
}
