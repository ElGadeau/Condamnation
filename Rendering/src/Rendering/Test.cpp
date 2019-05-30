#include "stdafx.h"

#include <Rendering/Test.h>
#include <Rendering/Context/OpenGL/GLFWDevice.h>
#include <Rendering/Context/OpenGL/GLEWDriver.h>

void TestGoodRendering()
{
    Rendering::Context::OpenGL::GLFWDevice device{};
    Rendering::Context::OpenGL::GLEWDriver driver{};

    while (!device.ShouldClose())
    {
        device.RefreshEvents();

        driver.Clear();
        device.Render();
    }
}

void TestBadRendering()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        // fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
        std::cerr << "Error: " << glewGetErrorString(err) << '\n';
    }

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return;
}
