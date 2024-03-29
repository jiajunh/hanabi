#pragma once
#ifndef HANABI_LAYER_H
#define HANABI_LAYER_H

#include "Core/base.h"
#include "Events/Event.h"

namespace Hanabi {

    class Layer {
    public:
        Layer(const std::string &name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate(float ts) {}
        virtual void OnImGuiRender() {}
        virtual void OnEvent(Event &event) {}

        const std::string &GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };
}

#endif