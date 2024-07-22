#include "buffer.h"
#include "cameramovement.h"
#include "cameratransform.h"
#include "pch.h"
#include "glew.h"
#include "glfw.h"
#include "global.h"
#include "input.h"
#include "light.h"
#include "material.h"
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

    tron::Buffer vbo(tron::BT_Array, tron::BP_Static | tron::BP_Draw);
    vbo.BufferData(points, sizeof points);

    tron::Buffer ebo(tron::BT_ElementArray, tron::BP_Static | tron::BP_Draw);
    ebo.BufferData(indices, sizeof indices);

    vbo.Use();
    const auto cubeVao        = tron::VertexArray::Create<glm::vec3, glm::vec3>();
    const auto lightSourceVao = tron::VertexArray::Create<glm::vec3, glm::vec3>();

    const tron::Program cubeProgram{
        { "assets/lighting.vert", tron::ST_Vertex },
        { "assets/lighting.frag", tron::ST_Fragment },
    };
    const tron::Program lightSourceProgram{
        { "assets/light-source.vert", tron::ST_Vertex },
        { "assets/light-source.frag", tron::ST_Fragment },
    };
    if (!cubeProgram || !lightSourceProgram)
    {
        perr("Couldn't load GL program");
        return 1;
    }

    tron::GameObject cube;
    cube.AddComponent<tron::obj::Transform>();

    tron::GameObject cube0;
    cube0.AddComponent<tron::obj::Transform>();

    tron::GameObject lightSource;
    lightSource.AddComponent<tron::obj::Transform>();

    tron::GameObject camera;
    camera.AddComponent<tron::obj::CameraTransform>();
    camera.AddComponent<tron::obj::CameraMovement>();

    cube.Awake();
    cube0.Awake();
    camera.Awake();
    cube.Start();
    cube0.Start();
    camera.Start();

    auto cubeTransform        = cube.GetComponent<tron::obj::Transform>();
    auto cube0Transform        = cube0.GetComponent<tron::obj::Transform>();
    auto lightSourceTransform = lightSource.GetComponent<tron::obj::Transform>();
    auto cameraTransform      = camera.GetComponent<tron::obj::CameraTransform>();

    cubeTransform->Position        = { 0, -0.3f, 3 };
    cube0Transform->Position        = { 1, -0.3f, 0 };
    lightSourceTransform->Position = { 0.5f, 0.3f, 1 };
    lightSourceTransform->Scale    = { 0.2f, 0.2f, 0.2f };

    tron::Buffer materialSsbo(tron::BT_ShaderStorage, tron::BP_Static | tron::BP_Draw);
    tron::Material material(
        32,
        { 1, 0.5f, 0.31f },
        { 1, 0.5f, 0.31f },
        { 0.5f, 0.5f, 0.5f }
    );
    material.LoadOn(materialSsbo);

    tron::Buffer lightSsbo(tron::BT_ShaderStorage, tron::BP_Static | tron::BP_Draw);
    tron::PointLight light(
        lightSourceTransform->Position,
        { 1, 1, 1 }
    );
    light.AttenuationRange = 50;
    light.LoadOn(lightSsbo);


    while (!glfwWindowShouldClose(glfw.GetWindow()))
    {
        glfw.Update();
        tron::TimeManager::Update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0, .3, .7, 1);

        cube.Update();
        camera.Update();

        /* Cube */
        materialSsbo.Use(1);
        lightSsbo.Use(2);
        cubeProgram.Use();

        cubeProgram.GetUniform<int>("fLightCount") = 1;
        cubeProgram.GetUniform<glm::vec3>("fViewPosition")   = cameraTransform->Position;
        cubeProgram.GetUniform<glm::mat4>("vProjectionView") = *cameraTransform;

        cubeVao.Use();
        ebo.Use();

        cubeProgram.GetUniform<glm::mat4>("vModel")          = *cubeTransform;
        glDrawElements(GL_TRIANGLES, std::size(indices), GL_UNSIGNED_INT, nullptr);

        cubeProgram.GetUniform<glm::mat4>("vModel")          = *cube0Transform;
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
