#include "buffer.h"
#include "pch.h"
#include "glew.h"
#include "glfw.h"
#include "global.h"
#include "shader.h"
#include "texture.h"
#include "vertexarray.h"

int main(int, char* argv[])
{
    tron::Global::Path = std::filesystem::path(argv[0]).parent_path().string();

    tron::GLFW glfw;
    if (!glfw)
        return 1;

    tron::GLEW glew;

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    GLfloat points[] = {
        // positions         // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
       -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
       -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };
    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    auto tex = tron::Texture("assets/wall.jpg", tron::TF_MIPMAP);

    tex.Use();

    tron::Buffer vbo(tron::BT_Array, tron::BP_Static | tron::BP_Draw);
    vbo.BufferData(points, sizeof points);

    tron::Buffer ebo(tron::BT_ElementArray, tron::BP_Static | tron::BP_Draw);
    ebo.BufferData(indices, sizeof indices);

    vbo.Use();
    const auto vao = tron::VertexArray::Create<glm::vec3, glm::vec3, glm::vec2>();


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

        vao.Use();
        ebo.Use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }

    return 0;
}
