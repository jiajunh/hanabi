#include "Renderer/Renderer.h"
#include "Core/base.h"
#include "Logs/Log.h"
#include "Renderer/Camera.h"
#include "Renderer/RenderCommand.h"
#include "pch.h"

#include <glm/gtx/string_cast.hpp>

namespace Hanabi {

    Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();

    void Renderer::Init() {
        RenderCommand::Init();
        // Renderer2D::Init();
    }

    void Renderer::Shutdown() {
        // Renderer2D::Shutdown();
    }

    void Renderer::OnWindowResize(uint32_t width, uint32_t height) {
        // RenderCommand::SetViewport(0, 0, width, height);
    }

    void Renderer::BeginScene(Camera &camera) {
        s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene() {
    }

    void Renderer::Submit(const Ref<Shader> &shader,
                          const Ref<VertexArray> &vertexArray,
                          const glm::mat4 &transform) {
        shader->Bind();
        shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader->SetMat4("u_Transform", transform);
        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }

    void Renderer::Submit(const Ref<Shader> &shader,
                          const Ref<VertexArray> &vertexArray,
                          uint32_t vertexCount,
                          const glm::mat4 &transform) {
        shader->Bind();
        shader->SetMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);
        shader->SetMat4("u_Transform", transform);
        vertexArray->Bind();
        RenderCommand::DrawLines(vertexArray, vertexCount);
    }

}