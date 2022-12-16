#pragma once
#ifndef HANABI_OPENGLCONTEXT_H
#define HANABI_OPENGLCONTEXT_H

#include "Renderer/GraphicsContext.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace Hanabi {

    class OpenGLContext : public GraphicsContext {

    public:
        OpenGLContext(GLFWwindow *windowHandle);
        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow *m_WindowHandle;
    };
}

#endif