#include "Renderer/RenderApi.h"
#include "Core/base.h"
#include "OpenGL/OpenGLRenderApi.h"

namespace Hanabi {

    RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

    Scope<RendererAPI> RendererAPI::Create() {
        return CreateScope<OpenGLRendererAPI>();
    }

}