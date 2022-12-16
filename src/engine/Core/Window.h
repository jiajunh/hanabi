#pragma once
#ifndef HANABI_WINDOW_H
#define HANABI_WINDOW_H

#include "Core/base.h"
#include "Events/Event.h"

namespace Hanabi {

    struct WindowProps {
        std::string Title;
        int Width;
        int Height;
        WindowProps(const std::string &title = "Hanabi Engine",
                    int width = 800,
                    int height = 500)
            : Title(title), Width(width), Height(height) {
        }
    };

    class Window {
    public:
        using EventCallbackFn = std::function<void(Event &)>;

        virtual ~Window() = default;

        virtual void OnUpdate() = 0;

        virtual int GetWidth() const = 0;
        virtual int GetHeight() const = 0;

        // Window attributes
        virtual void SetEventCallback(const EventCallbackFn &callback) = 0;
        // virtual void SetVSync(bool enabled) = 0;
        // virtual bool IsVSync() const = 0;

        virtual void *GetNativeWindow() const = 0;

        static Scope<Window> Create(const WindowProps &props = WindowProps());
    };
}

#endif