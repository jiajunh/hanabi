#include "Application.h"
#include "Core/Input.h"
#include "Core/Time.h"
#include "Core/Window.h"
#include "Core/base.h"
#include "Events/Event.h"

#include "Logs/Log.h"

// #include <glad/glad.h>

// #include <GLFW/glfw3.h>

namespace Hanabi {

    Application *Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = this;
        m_Window = Window::Create();
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        // VAO, VBO, IndexBuffer, Shader
    }

    Application::~Application() {}

    void Application::Run() {
        while (m_Running) {
            float curTime = Time::GetTime();
            float deltaTime = curTime - m_LastFrameTime;
            m_LastFrameTime = curTime;
            for (Layer *layer : m_LayerStack) {
                layer->OnUpdate(deltaTime);
            }
            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e) {
        // HANABI_CORE_INFO("{}", e.ToString());
        if (e.GetEventType() == EventType::KeyPressed) {
            KeyEvent &event = (KeyPressedEvent &)e;
            HANABI_INFO("{0}", event.GetKeyCode());
        }

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(HANABI_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(HANABI_BIND_EVENT_FN(Application::OnWindowResize));
    }

    bool Application::OnWindowClose(WindowCloseEvent &e) {
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent &e) {
        return false;
    }

    void Application::PushLayer(Layer *layer) {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer *layer) {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }

}
