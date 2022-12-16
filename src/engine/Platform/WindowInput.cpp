#include "Application/Application.h"
#include "Core/Input.h"
#include "pch.h"

#include <GLFW/glfw3.h>

namespace Hanabi {

    bool Input::IsKeyPressed(KeyCode key) {
        auto *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, static_cast<int>(key));
        return state == GLFW_PRESS;
    }

    bool Input::IsMouseButtonPressed(MouseCode button) {
        auto *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, static_cast<int>(button));
        return state == GLFW_PRESS;
    }

    std::pair<float, float> Input::GetMousePosition() {
        auto *window = static_cast<GLFWwindow *>(Application::Get().GetWindow().GetNativeWindow());
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return {(float)xpos, (float)ypos};
    }

    float Input::GetMouseX() {
        return GetMousePosition().first;
    }

    float Input::GetMouseY() {
        return GetMousePosition().second;
    }
}