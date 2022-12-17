#pragma once
#ifndef HANABI_INPUT_H
#define HANABI_INPUT_H

#include "Core/KeyCode.h"
#include "Core/MouseCode.h"

#include <glm/glm.hpp>

namespace Hanabi {
    class Input {
    public:
        static bool IsKeyPressed(KeyCode key);
        static bool IsMouseButtonPressed(MouseCode button);
        static std::pair<float, float> GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };
}

#endif