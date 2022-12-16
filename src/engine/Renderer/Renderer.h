#pragma once
#ifndef HANABI_RENDERER_H
#define HANABI_RENDERER_H

#include "Core/base.h"
#include "Renderer/Camera.h"
#include "Renderer/RenderApi.h"
#include "Renderer/Shader.h"
#include "Renderer/VertexArray.h"

#include <glm/glm.hpp>

namespace Hanabi {

    class Renderer {
    public:
        static void Init();
        static void Shutdown();

        static void OnWindowResize(uint32_t width, uint32_t height);

        static void BeginScene(Camera &camera);
        static void EndScene();

        static void Submit(const Ref<Shader> &shader,
                           const Ref<VertexArray> &vertexArray,
                           const glm::mat4 &transform = glm::mat4(1.0f));

        static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    private:
        struct SceneData {
            glm::mat4 ViewProjectionMatrix;
        };

        static Scope<SceneData> s_SceneData;
    };
}

#endif