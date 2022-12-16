#include "Core/Window.h"
#include "Platform/MacWindow.h"
#include "pch.h"

namespace Hanabi {

    Scope<Window> Window::Create(const WindowProps &props) {
        return CreateScope<MacWindow>(props);
    }

}