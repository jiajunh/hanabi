#include "Application.h"
#include "Core/Input.h"
#include "Core/Timestep.h"
#include "Core/Window.h"
#include "Core/base.h"
#include "Events/Event.h"
#include "ImGui/ImGuiLayer.h"

#include "Logs/Log.h"

// #include <glad/glad.h>

// #include <GLFW/glfw3.h>

namespace Hanabi {

    Application *Application::s_Instance = nullptr;

    Application::Application() {
        s_Instance = this;
        m_Window = Window::Create();
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        m_ImGuiLayer = new ImGuiLayer();
        PushOverlay(m_ImGuiLayer);
        // VAO, VBO, IndexBuffer, Shader
    }

    Application::~Application() {}

    void Application::Run() {
        while (m_Running) {
            float curTime = Timer::GetTime();
            float deltaTime = curTime - m_LastFrameTime;
            m_LastFrameTime = curTime;
            for (Layer *layer : m_LayerStack) {
                layer->OnUpdate(deltaTime);
            }

            m_ImGuiLayer->Begin();
            for (Layer *layer : m_LayerStack) {
                layer->OnImGuiRender();
            }
            m_ImGuiLayer->End();
            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event &e) {

        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(HANABI_BIND_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<WindowResizeEvent>(HANABI_BIND_EVENT_FN(Application::OnWindowResize));

        for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it) {
            if (e.Handled)
                break;
            (*it)->OnEvent(e);
        }
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
