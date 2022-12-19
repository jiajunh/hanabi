#include "Renderer/Texture.h"
#include "OpenGL/OpenGLTexture.h"

namespace Hanabi {

    Ref<Texture2D> Texture2D::Create(const std::string &path) {
        return CreateRef<OpenGLTexture2D>(path);
    }
}