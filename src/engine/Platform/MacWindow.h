#pragma once
#ifndef HANABI_MACWINDOW_H
#define HANABI_MACWINDOW_H

#include "Core/Window.h"
#include "Renderer/GraphicsContext.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace Hanabi {
    class MacWindow : public Window {
    public:
        MacWindow(const WindowProps &props);
        virtual ~MacWindow();
        void OnUpdate() override;

        int GetWidth() const override { return m_Data.Width; }
        int GetHeight() const override { return m_Data.Height; }

        void SetEventCallback(const EventCallbackFn &callback) override { m_Data.EventCallback = callback; }
        // void SetVSync(bool enabled) override;
        // bool IsVSync() const override;

        virtual void *GetNativeWindow() const override { return m_Window; }

    private:
        GLFWwindow *m_Window;
        Scope<GraphicsContext> m_Context;

        struct WindowData {
            std::string Title;
            unsigned int Width, Height;
            // bool VSync;
            EventCallbackFn EventCallback;
        };

        WindowData m_Data;

        virtual void Init(const WindowProps &props);
        virtual void Shutdown();
    };
}

#endif