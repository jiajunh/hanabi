#include "Renderer/Shader.h"
#include "Core/base.h"
#include "OpenGL/OpenGLShader.h"

namespace Hanabi {

    Ref<Shader> Shader::Create(const std::string &filepath) {
        return CreateRef<OpenGLShader>(filepath);
    }

    Ref<Shader> Shader::Create(const std::string &name, const std::string &vertexSrc, const std::string &fragmentSrc) {
        return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
    }

}