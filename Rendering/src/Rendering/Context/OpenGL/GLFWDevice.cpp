#include "stdafx.h"
#include <Rendering/Context/OpenGL/GLFWDevice.h>

using namespace Rendering::Context::OpenGL;

GLFWDevice::GLFWDevice() noexcept
{
    Init();
}

GLFWDevice::~GLFWDevice() noexcept
{
    glfwTerminate();
}

void GLFWDevice::Init() noexcept
{
    glfwInit();

    m_window = std::make_shared<GLFWWindow>();

    //Debug
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);

    //OpenGL Context Configuration
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwMakeContextCurrent(std::any_cast<GLFWwindow*>(m_window->Data()));

    lastTime = glfwGetTime();
    MAX_FPS = 60;
}

bool GLFWDevice::ShouldClose() const noexcept
{
    return m_window->ShouldClose();
}

void GLFWDevice::Render() const noexcept
{
    glfwSwapBuffers(std::any_cast<GLFWwindow*>(m_window->Data()));
}

void GLFWDevice::RefreshEvents() const noexcept
{
    glfwPollEvents();
}

std::shared_ptr<GLFWWindow> GLFWDevice::GetWindow() const noexcept
{
    return m_window;
}

void GLFWDevice::CalculateDeltaTime() noexcept
{
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    deltaTime *= MAX_FPS;
    lastTime = currentTime;
}

float GLFWDevice::GetDeltaTime() const noexcept
{
    return deltaTime;
}

void GLFWDevice::Close()
{
    glfwSetWindowShouldClose(std::any_cast<GLFWwindow*>(m_window->Data()), true);
}
