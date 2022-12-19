#ifndef HANABI_APPLICATION_H
#define HANABI_APPLICATION_H

#include "Core/Window.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Events/MouseEvent.h"
#include "ImGui/ImGuiLayer.h"
#include "Layers/LayerStack.h"
#include "pch.h"

namespace Hanabi {
    class Application {
    public:
        Application();
        virtual ~Application();
        inline static Application &Get() { return *s_Instance; }
        inline Window &GetWindow() { return *m_Window; }
        void OnEvent(Event &e);
        void PushLayer(Layer *layer);
        void PushOverlay(Layer *layer);
        void Run();

    private:
        static Application *s_Instance;
        Scope<Window> m_Window;
        bool m_Running = true;
        LayerStack m_LayerStack;

        // std::unique_ptr<ImGuiLayer> m_ImGuiLayer;
        ImGuiLayer *m_ImGuiLayer;

        float m_LastFrameTime = 0.0f;

        bool OnWindowClose(WindowCloseEvent &e);
        bool OnWindowResize(WindowResizeEvent &e);
    };
}

#endif
