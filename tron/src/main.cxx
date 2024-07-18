#include "buffer.h"
#include "cameratransform.h"
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

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    glfwSetInputMode(glfw.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
    tron::CameraTransform camera;
    float fov = 45;

    while (!glfwWindowShouldClose(glfw.GetWindow()))
    {
        static float last;
        const auto   current = static_cast<float>(glfwGetTime());
        float        delta   = current - last;
        last                 = current;

        static auto lastCursor = glfw.Cursor;
        auto cursorOffset = glfw.Cursor - lastCursor;
        lastCursor = glfw.Cursor;

        constexpr float sensitivity = 0.001f;
        cursorOffset *= sensitivity;

        fov -= glfw.Scroll;
        if (fov < 1)
            fov = 1;
        else if (fov > 75)
            fov = 75;

        glfw.Update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, .3, .7, 1);


        tron::Transform transform;
        transform.Position = { 0, 0, -3 };

        camera.Yaw += cursorOffset.x;
        camera.Pitch += cursorOffset.y;

        if (camera.Pitch > glm::radians(85.f))
            camera.Pitch = glm::radians(85.f);
        else if (camera.Pitch < -glm::radians(85.f))
            camera.Pitch = -glm::radians(85.f);

        glm::vec3 up = glm::vec3(0, 1, 0);

        if (glfwGetKey(glfw.GetWindow(), GLFW_KEY_W))
            view.Position += camera.Front * delta;
        if (glfwGetKey(glfw.GetWindow(), GLFW_KEY_S))
            view.Position -= camera.Front * delta;
        if (glfwGetKey(glfw.GetWindow(), GLFW_KEY_A))
            view.Position -= normalize(cross(camera.Front, up)) * delta;
        if (glfwGetKey(glfw.GetWindow(), GLFW_KEY_D))
            view.Position += normalize(cross(camera.Front, up)) * delta;

        if (glfwGetKey(glfw.GetWindow(), GLFW_KEY_SPACE))
            view.Position += glm::vec3(0, 1, 0) * delta;
        if (glfwGetKey(glfw.GetWindow(), GLFW_KEY_LEFT_SHIFT))
            view.Position += glm::vec3(0, -1, 0) * delta;

        glm::mat4 viewMat = glm::lookAt(view.Position, view.Position + camera.Front, up);

        glm::mat4 projection;
        projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);

        program.GetUniform<glm::mat4>("vTransform") =
            projection
            * static_cast<glm::mat4>(viewMat)
            * static_cast<glm::mat4>(transform);

        vao.Use();
        ebo.Use();
        glDrawElements(GL_TRIANGLES, std::size(indices), GL_UNSIGNED_INT, nullptr);
    }

    return 0;
}
