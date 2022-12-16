#pragma once
#ifndef HANABI_TIME_H
#define HANABI_TIME_H

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace Hanabi {

    class Time {
    public:
        static float GetTime() {
            return (float)glfwGetTime();
        }
    };

}

#endif