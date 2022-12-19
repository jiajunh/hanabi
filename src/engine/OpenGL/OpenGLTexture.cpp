#include "OpenGL/OpenGLTexture.h"
#include "Logs/Log.h"
#include "pch.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>

namespace Hanabi {

    OpenGLTexture2D::OpenGLTexture2D(const std::string &path) : m_Path(path) {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc *data = nullptr;
        {
            data = stbi_load(path.c_str(), &width, &height, &channels, 0);
        }

        // HANABI_CORE_WARN("{0}, {1}, {2}", width, height, channels);

        if (data) {
            m_IsLoaded = true;

            m_Width = width;
            m_Height = height;

            GLint internalFormat = 0, dataFormat = 0;
            if (channels == 4) {
                internalFormat = GL_RGBA8;
                dataFormat = GL_RGBA;
            } else if (channels == 3) {
                internalFormat = GL_RGB8;
                dataFormat = GL_RGB;
            }

            m_InternalFormat = internalFormat;
            m_DataFormat = dataFormat;

            glGenTextures(1, &m_RendererID);
            glBindTexture(GL_TEXTURE_2D, m_RendererID);
            // set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            stbi_image_free(data);
        }
    }

    OpenGLTexture2D::~OpenGLTexture2D() {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);
    }

}