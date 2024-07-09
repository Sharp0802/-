#include "buffer.h"
#include "pch.h"
#include "glew.h"
#include "glfw.h"
#include "global.h"
#include "shader.h"
#include "texture.h"
#include "transform.h"
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

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#define H 0.5f


    GLfloat points[] = {
        // vert      // colors  // texture coords

        // +X
        +H, +H, -H, 1, 1, 1, 1, 1,
        +H, -H, -H, 1, 1, 1, 1, 0,
        +H, -H, +H, 1, 1, 1, 0, 0,
        +H, +H, +H, 1, 1, 1, 0, 1,

        -H, +H, +H, 1, 1, 1, 1, 1,
        -H, -H, +H, 1, 1, 1, 1, 0,
        -H, -H, -H, 1, 1, 1, 0, 0,
        -H, +H, -H, 1, 1, 1, 0, 1,

        // +Y
        +H, +H, -H, 1, 1, 1, 1, 1,
        +H, +H, +H, 1, 1, 1, 1, 0,
        -H, +H, +H, 1, 1, 1, 0, 0,
        -H, +H, -H, 1, 1, 1, 0, 1,

        -H, -H, -H, 1, 1, 1, 1, 1,
        -H, -H, +H, 1, 1, 1, 1, 0,
        +H, -H, +H, 1, 1, 1, 0, 0,
        +H, -H, -H, 1, 1, 1, 0, 1,

        // +Z
        +H, +H, +H, 1, 1, 1, 1, 1,
        +H, -H, +H, 1, 1, 1, 1, 0,
        -H, -H, +H, 1, 1, 1, 0, 0,
        -H, +H, +H, 1, 1, 1, 0, 1,

        -H, +H, -H, 1, 1, 1, 1, 1,
        -H, -H, -H, 1, 1, 1, 1, 0,
        +H, -H, -H, 1, 1, 1, 0, 0,
        +H, +H, -H, 1, 1, 1, 0, 1,
    };
#define RECT_INDEICE(n) 0+4*n, 1+4*n, 3+4*n, 1+4*n, 2+4*n, 3+4*n
    GLuint indices[] = {
        RECT_INDEICE(0),
        RECT_INDEICE(1),
        RECT_INDEICE(2),
        RECT_INDEICE(3),
        RECT_INDEICE(4),
        RECT_INDEICE(5),
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

    tron::Transform view;

    while (!glfwWindowShouldClose(glfw.GetWindow()))
    {
        static float last;
        const auto current = static_cast<float>(glfwGetTime());
        float delta        = current - last;
        last               = current;

        glfw.Update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, .3, .7, 1);


        tron::Transform transform;
        transform.Position = { 0, sin(glfwGetTime()) * 0.1f, 0 };
        transform.Rotation = { glm::vec3(0, static_cast<float>(glfwGetTime()), 0) };

        if (glfwGetKey(glfw.GetWindow(), GLFW_KEY_W))
            view.Position += glm::vec3(0, 0, 1) * delta;
        if (glfwGetKey(glfw.GetWindow(), GLFW_KEY_S))
            view.Position += glm::vec3(0, 0, -1) * delta;
        if (glfwGetKey(glfw.GetWindow(), GLFW_KEY_A))
            view.Position += glm::vec3(1, 0, 0) * delta;
        if (glfwGetKey(glfw.GetWindow(), GLFW_KEY_D))
            view.Position += glm::vec3(-1, 0, 0) * delta;

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);


        program.GetUniform<glm::mat4>("vTransform") =
            projection
            * static_cast<glm::mat4>(view)
            * static_cast<glm::mat4>(transform);

        vao.Use();
        ebo.Use();
        glDrawElements(GL_TRIANGLES, std::size(indices), GL_UNSIGNED_INT, nullptr);
    }

    return 0;
}
