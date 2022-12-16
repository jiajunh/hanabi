#include "Renderer/VertexArray.h"
#include "Core/base.h"
#include "OpenGL/OpenGLVertexArray.h"

namespace Hanabi {

    Ref<VertexArray> VertexArray::Create() {
        return CreateRef<OpenGLVertexArray>();
    }

}