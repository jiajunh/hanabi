#pragma once
#ifndef HANABI_RENDERCOMMAND_H
#define HANABI_RENDERCOMMAND_H

#include "Core/base.h"
#include "Renderer/RenderApi.h"

#include <glm/glm.hpp>

namespace Hanabi {

    class RenderCommand {
    public:
        static void Init() {
            s_RendererAPI->Init();
        }

        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) {
            s_RendererAPI->SetViewport(x, y, width, height);
        }

        static void SetClearColor(const glm::vec4 &color) {
            s_RendererAPI->SetClearColor(color);
        }

        static void Clear() {
            s_RendererAPI->Clear();
        }

        static void DrawIndexed(const Ref<VertexArray> &vertexArray, uint32_t indexCount = 0) {
            s_RendererAPI->DrawIndexed(vertexArray, indexCount);
        }

        static void DrawLines(const Ref<VertexArray> &vertexArray, uint32_t vertexCount) {
            s_RendererAPI->DrawLines(vertexArray, vertexCount);
        }

        static void SetLineWidth(float width) {
            s_RendererAPI->SetLineWidth(width);
        }

        static void EnableDepthTest() {
            s_RendererAPI->EnableDepthTest();
        }

    private:
        static Scope<RendererAPI> s_RendererAPI;
    };

}

#endif
