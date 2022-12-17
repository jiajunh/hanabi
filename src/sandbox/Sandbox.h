#include "Hanabi.h"
#include "pch.h"

class ExampleLayer : public Hanabi::Layer {

public:
    ExampleLayer() : Layer("Example Base Layer"), m_Camera() {

        std::string cwd = std::filesystem::current_path().u8string();

        std::string vertex_shader_source = "/Users/jiajunh/Desktop/hanabi/src/shaders/TestVertexShader.vs";
        std::string fragment_shader_source = "/Users/jiajunh/Desktop/hanabi/src/shaders/TestFragmentShader.fs";

        m_Shader = Hanabi::Shader::Create("shader", vertex_shader_source, fragment_shader_source);

        // float vertices[] = {
        //     // For visualization: each row is a vertex.
        //     // Each vertex has position [x, y, z] and color [r, g, b]
        //     -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, // red color for this vertex
        //     0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // green color
        //     0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // blue color for our top vertex
        // };

        float cube_vertices[] = {
            // front
            -1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // x, y, z ,r, g, b
            1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // x, y, z ,r, g, b
            1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // x, y, z ,r, g, b
            -1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // x, y, z ,r, g, b
            // back
            -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, // x, y, z ,r, g, b
            1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f,  // x, y, z ,r, g, b
            1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,   // x, y, z ,r, g, b
            -1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // x, y, z ,r, g, b
        };

        m_VertexArray = Hanabi::VertexArray::Create();
        m_VertexBuffer = Hanabi::VertexBuffer::Create(cube_vertices, sizeof(cube_vertices));

        Hanabi::BufferLayout layout = {
            {Hanabi::ShaderDataType::Float3, "a_Position"},
            {Hanabi::ShaderDataType::Float4, "a_Color"}};

        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        // uint32_t indices[] = {0, 1, 2};
        uint32_t cube_elements[] = {
            // front
            0, 1, 2,
            2, 3, 0,
            // right
            1, 5, 6,
            6, 2, 1,
            // back
            7, 6, 5,
            5, 4, 7,
            // left
            4, 0, 3,
            3, 7, 4,
            // bottom
            4, 5, 1,
            1, 0, 4,
            // top
            3, 2, 6,
            6, 7, 3};
        Hanabi::Ref<Hanabi::IndexBuffer> indexBuffer = Hanabi::IndexBuffer::Create(cube_elements, 3 * 12);
        m_VertexArray->SetIndexBuffer(indexBuffer);
    }

    void OnAttach() override {
        HANABI_INFO("Example Layer OnAttach");
    }

    void OnEvent(Hanabi::Event &event) override {}

    void OnUpdate(float ts) override {

        // HANABI_TRACE("Delta time: {0} s", ts);

        Hanabi::RenderCommand::SetClearColor({0.1f, 0.1f, 0.1f, 1});
        Hanabi::RenderCommand::Clear();

        Hanabi::Renderer::BeginScene(m_Camera);

        m_Shader->Bind();
        m_VertexArray->Bind();

        Hanabi::Renderer::Submit(m_Shader, m_VertexArray);

        Hanabi::Renderer::EndScene();
    }

private:
    Hanabi::Ref<Hanabi::VertexArray> m_VertexArray;
    Hanabi::Ref<Hanabi::VertexBuffer> m_VertexBuffer;

    Hanabi::Ref<Hanabi::Shader> m_Shader;

    Hanabi::Camera m_Camera;
};

class SandboxApp : public Hanabi::Application {
public:
    SandboxApp() {
        PushLayer(new ExampleLayer());
    }
    ~SandboxApp() {}
};