#include "Hanabi.h"
#include "pch.h"

#include "imgui.h"

class ExampleLayer : public Hanabi::Layer {

public:
    ExampleLayer() : Layer("Example Base Layer"), m_Camera() {

        Hanabi::RenderCommand::EnableDepthTest();

        std::string cwd = std::filesystem::current_path().u8string();

        std::string vertex_shader_source = "/Users/jiajunh/Desktop/hanabi/src/shaders/TestVertexShader.vs";
        std::string fragment_shader_source = "/Users/jiajunh/Desktop/hanabi/src/shaders/TestFragmentShader.fs";

        std::string texture1_path = "/Users/jiajunh/Desktop/hanabi/src/gameObjData/um_logo.png";
        std::string texture2_path = "/Users/jiajunh/Desktop/hanabi/src/gameObjData/container.jpeg";

        m_Shader = Hanabi::Shader::Create("shader", vertex_shader_source, fragment_shader_source);

        m_Texture1 = Hanabi::Texture2D::Create(texture1_path);
        m_Texture2 = Hanabi::Texture2D::Create(texture2_path);

        float cube_vertices[] = {
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
            0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
            -0.5f, 0.5f, -0.5f, 0.0f, 1.0f};

        m_VertexArray = Hanabi::VertexArray::Create();
        m_VertexBuffer = Hanabi::VertexBuffer::Create(cube_vertices, sizeof(cube_vertices));

        Hanabi::BufferLayout layout = {
            {Hanabi::ShaderDataType::Float3, "a_Position"},
            {Hanabi::ShaderDataType::Float2, "a_Texture"}};

        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        // uint32_t cube_elements[] = {
        //     // front
        //     0, 1, 2,
        //     2, 3, 0,
        //     // right
        //     1, 5, 6,
        //     6, 2, 1,
        //     // back
        //     7, 6, 5,
        //     5, 4, 7,
        //     // left
        //     4, 0, 3,
        //     3, 7, 4,
        //     // bottom
        //     4, 5, 1,
        //     1, 0, 4,
        //     // top
        //     3, 2, 6,
        //     6, 7, 3};
        // Hanabi::Ref<Hanabi::IndexBuffer> indexBuffer = Hanabi::IndexBuffer::Create(cube_elements, 3 * 12);
        // m_VertexArray->SetIndexBuffer(indexBuffer);

        m_Shader->Bind();
        m_Shader->SetInt("texture1", 0);
        m_Shader->SetInt("texture2", 1);
    }

    void OnAttach() override {
        HANABI_INFO("Example Layer OnAttach");
    }

    void OnEvent(Hanabi::Event &event) override {
        m_Camera.OnEvent(event);
    }

    void OnUpdate(float ts) override {

        // HANABI_TRACE("Delta time: {0} s", ts);
        m_Camera.OnUpdate(ts);

        Hanabi::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Hanabi::RenderCommand::Clear();

        Hanabi::Renderer::BeginScene(m_Camera);

        m_Texture1->Bind(0);
        m_Texture2->Bind(1);

        m_Shader->Bind();
        m_VertexArray->Bind();

        Hanabi::Renderer::Submit(m_Shader, m_VertexArray, 36);

        Hanabi::Renderer::EndScene();
    }

    void OnImGuiRender() override {
        ImGui::Begin("Settings");
        ImGui::Text("Hello from another window!");
        ImGui::End();
    }

private:
    Hanabi::Ref<Hanabi::VertexArray> m_VertexArray;
    Hanabi::Ref<Hanabi::VertexBuffer> m_VertexBuffer;
    Hanabi::Ref<Hanabi::Shader> m_Shader;
    Hanabi::Camera m_Camera;
    Hanabi::Ref<Hanabi::Texture2D> m_Texture1, m_Texture2;
};

class SandboxApp : public Hanabi::Application {
public:
    SandboxApp() {
        PushLayer(new ExampleLayer());
    }
    ~SandboxApp() {}
};