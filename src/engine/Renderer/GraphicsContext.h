#pragma once
#ifndef HANABI_GRAPHICCONTEXT_H
#define HANABI_GRAPHICCONTEXT_H

#include "Core/base.h"

namespace Hanabi {

    class GraphicsContext {
    public:
        virtual ~GraphicsContext() = default;
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
        static Scope<GraphicsContext> Create(void *window);
    };
}

#endif