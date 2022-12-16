#include "OpenGL/OpenGLContext.h"
#include "Core/HanabiAssert.h"
#include "Logs/Log.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace Hanabi {

    OpenGLContext::OpenGLContext(GLFWwindow *windowHandle) : m_WindowHandle(windowHandle) {}

    void OpenGLContext::Init() {

        glfwMakeContextCurrent(m_WindowHandle);

        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

        HANABI_ASSERT(status, "Failed to initialize Glad!");

        HANABI_CORE_INFO("OpenGL Info:");
        HANABI_CORE_INFO("  Vendor: {0}", reinterpret_cast<const char *>(glGetString(GL_VENDOR)));
        HANABI_CORE_INFO("  Renderer: {0}", reinterpret_cast<const char *>(glGetString(GL_RENDERER)));
        HANABI_CORE_INFO("  Version: {0}", reinterpret_cast<const char *>(glGetString(GL_VERSION)));
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }
}