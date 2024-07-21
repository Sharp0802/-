#include "buffer.h"
#include "cameramovement.h"
#include "cameratransform.h"
#include "pch.h"
#include "glew.h"
#include "glfw.h"
#include "global.h"
#include "input.h"
#include "screen.h"
#include "shader.h"
#include "texture.h"
#include "ttime.h"
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

    tron::Input::SetContext(&glfw);
    tron::Screen::SetContext(&glfw);

#define H 0.5f


    GLfloat points[] = {
        // +X
        +H, +H, -H, 1, 0, 0,
        +H, -H, -H, 1, 0, 0,
        +H, -H, +H, 1, 0, 0,
        +H, +H, +H, 1, 0, 0,

        -H, +H, +H, -1, 0, 0,
        -H, -H, +H, -1, 0, 0,
        -H, -H, -H, -1, 0, 0,
        -H, +H, -H, -1, 0, 0,

        // +Y
        +H, +H, -H, 0, 1, 0,
        +H, +H, +H, 0, 1, 0,
        -H, +H, +H, 0, 1, 0,
        -H, +H, -H, 0, 1, 0,

        -H, -H, -H, 0, -1, 0,
        -H, -H, +H, 0, -1, 0,
        +H, -H, +H, 0, -1, 0,
        +H, -H, -H, 0, -1, 0,

        // +Z
        +H, +H, +H, 0, 0, 1,
        +H, -H, +H, 0, 0, 1,
        -H, -H, +H, 0, 0, 1,
        -H, +H, +H, 0, 0, 1,

        -H, +H, -H, 0, 0, -1,
        -H, -H, -H, 0, 0, -1,
        +H, -H, -H, 0, 0, -1,
        +H, +H, -H, 0, 0, -1,
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
    const auto cubeVao = tron::VertexArray::Create<glm::vec3, glm::vec3>();
    const auto lightSourceVao = tron::VertexArray::Create<glm::vec3, glm::vec3>();

    const tron::Program cubeProgram{
        { "assets/lighting.vert", tron::ST_Vertex },
        { "assets/lighting.frag", tron::ST_Fragment },
    };
    if (!cubeProgram)
    {
        perr("Couldn't load GL program");
        return 1;
    }
    const tron::Program lightSourceProgram{
            { "assets/light-source.vert", tron::ST_Vertex },
            { "assets/light-source.frag", tron::ST_Fragment },
        };
    if (!lightSourceProgram)
    {
        perr("Couldn't load GL program");
        return 1;
    }


    tron::GameObject cube;
    cube.AddComponent<tron::obj::Transform>();

    tron::GameObject lightSource;
    lightSource.AddComponent<tron::obj::Transform>();

    tron::GameObject camera;
    camera.AddComponent<tron::obj::CameraTransform>();
    camera.AddComponent<tron::obj::CameraMovement>();

    cube.Awake();
    camera.Awake();
    cube.Start();
    camera.Start();

    auto cubeTransform = cube.GetComponent<tron::obj::Transform>();
    auto lightSourceTransform = lightSource.GetComponent<tron::obj::Transform>();
    auto cameraTransform = camera.GetComponent<tron::obj::CameraTransform>();

    cubeTransform->Position = { 0, -0.3f, 3 };
    lightSourceTransform->Position = { 1, 0.3f, 2 };
    lightSourceTransform->Scale = { 0.2f, 0.2f, 0.2f };

    while (!glfwWindowShouldClose(glfw.GetWindow()))
    {
        glfw.Update();
        tron::TimeManager::Update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, .3, .7, 1);

        cube.Update();
        camera.Update();

        /* Cube */
        cubeProgram.Use();

        cubeProgram.GetUniform<glm::vec3>("fLightColor") = { 1, 1, 1 };
        cubeProgram.GetUniform<glm::vec3>("fLightPosition") = lightSourceTransform->Position;
        cubeProgram.GetUniform<glm::vec3>("fViewPosition") = cameraTransform->Position;

        cubeProgram.GetUniform<glm::vec3>("fMaterial.Ambient") = glm::vec3{ 1, 0.5f, 0.31f };
        cubeProgram.GetUniform<glm::vec3>("fMaterial.Diffuse") = { 1, 0.5f, 0.31f };
        cubeProgram.GetUniform<glm::vec3>("fMaterial.Specular") = { 0.5f, 0.5f, 0.5f };
        cubeProgram.GetUniform<float>("fMaterial.Shininess") = 32;

        cubeProgram.GetUniform<glm::mat4>("vProjectionView") = *cameraTransform;
        cubeProgram.GetUniform<glm::mat4>("vModel")      = *cubeTransform;

        cubeVao.Use();
        ebo.Use();
        glDrawElements(GL_TRIANGLES, std::size(indices), GL_UNSIGNED_INT, nullptr);

        /* Light source */
        lightSourceProgram.Use();
        lightSourceProgram.GetUniform<glm::mat4>("vTransform") =
            static_cast<glm::mat4>(*cameraTransform)
            * static_cast<glm::mat4>(*lightSourceTransform);

        lightSourceVao.Use();
        ebo.Use();
        glDrawElements(GL_TRIANGLES, std::size(indices), GL_UNSIGNED_INT, nullptr);
    }

    return 0;
}
