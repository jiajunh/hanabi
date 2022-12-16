#include "OpenGL/OpenGLShader.h"
#include "Logs/Log.h"
#include "pch.h"

#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include <GLFW/glfw3.h>

namespace Hanabi {

    OpenGLShader::OpenGLShader(const std::string &filepath)
        : m_FilePath(filepath) {

        // std::string source = ReadFile(filepath);

        // CreateProgram();

        // // Extract name from filepath
        // auto lastSlash = filepath.find_last_of("/\\");
        // lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        // auto lastDot = filepath.rfind('.');
        // auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        // m_Name = filepath.substr(lastSlash, count);
    }

    OpenGLShader::OpenGLShader(const std::string &name,
                               const std::string &vertexSrc,
                               const std::string &fragmentSrc) {

        GLint Result = GL_FALSE;
        int InfoLogLength;

        m_VertexShader = glCreateShader(GL_VERTEX_SHADER);
        m_FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        std::string vertexShaderString = ReadFile(vertexSrc);
        const char *vertexShaderCode = vertexShaderString.c_str();
        glShaderSource(m_VertexShader, 1, &vertexShaderCode, NULL);
        glCompileShader(m_VertexShader);

        // Check Vertex Shader
        glGetShaderiv(m_VertexShader, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(m_VertexShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(m_VertexShader, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            HANABI_CORE_ERROR("{0}", &VertexShaderErrorMessage[0]);
        }

        std::string fragmentShaderString = ReadFile(fragmentSrc);
        const char *fragmentShaderCode = fragmentShaderString.c_str();
        glShaderSource(m_FragmentShader, 1, &fragmentShaderCode, NULL);
        glCompileShader(m_FragmentShader);

        // Check Fragment Shader
        glGetShaderiv(m_FragmentShader, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(m_FragmentShader, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(m_FragmentShader, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            HANABI_CORE_ERROR("{0}", &FragmentShaderErrorMessage[0]);
        }

        CreateProgram();
    }

    OpenGLShader::~OpenGLShader() {
        glDeleteProgram(m_ShaderProgram);
    }

    void OpenGLShader::Bind() const {
        glUseProgram(m_ShaderProgram);
    }

    void OpenGLShader::Unbind() const {
        glUseProgram(0);
    }

    std::string OpenGLShader::ReadFile(const std::string &filepath) {
        // Read the Shader code from the file
        std::string ShaderCode;
        std::ifstream ShaderStream(filepath, std::ios::in);
        if (ShaderStream.is_open()) {
            std::stringstream sstr;
            sstr << ShaderStream.rdbuf();
            ShaderCode = sstr.str();
            ShaderStream.close();
        } else {
            HANABI_CORE_ERROR("Can't open shader path: {0}", filepath);
        }
        return ShaderCode;
    }

    void OpenGLShader::CreateProgram() {
        GLint Result = GL_FALSE;
        int InfoLogLength;

        GLuint program = glCreateProgram();
        // Link the program
        glAttachShader(program, m_VertexShader);
        glAttachShader(program, m_FragmentShader);
        glLinkProgram(program);

        // Check the program
        glGetProgramiv(program, GL_LINK_STATUS, &Result);
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &InfoLogLength);

        if (InfoLogLength > 0) {
            std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
            glGetProgramInfoLog(program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            HANABI_CORE_ERROR(&ProgramErrorMessage[0]);
        }

        m_ShaderProgram = program;

        glDetachShader(program, m_VertexShader);
        glDetachShader(program, m_FragmentShader);

        glDeleteShader(m_VertexShader);
        glDeleteShader(m_FragmentShader);
    }

    void OpenGLShader::SetMat4(const std::string &name, const glm::mat4 &value) {
        UploadUniformMat4(name, value);
    }

    void OpenGLShader::UploadUniformMat4(const std::string &name, const glm::mat4 &matrix) {
        GLint location = glGetUniformLocation(m_ShaderProgram, name.c_str());
        // glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
        glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
    }

}