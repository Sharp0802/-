#include "pch.h"
#include "glew.h"
#include "glfw.h"
#include "global.h"
#include "shader.h"

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


    const tron::Program program{
        { "assets/sample.vert", tron::ST_Vertex },
        { "assets/sample.frag", tron::ST_Fragment },
    };
    if (!program)
    {
        perr("Couldn't load GL program");
        return 1;
    }

    program.Use();

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
