#include "Renderer/GraphicsContext.h"
#include "OpenGL/OpenGLContext.h"

namespace Hanabi {

    Scope<GraphicsContext> GraphicsContext::Create(void *window) {
        return CreateScope<OpenGLContext>(static_cast<GLFWwindow *>(window));
    }

}