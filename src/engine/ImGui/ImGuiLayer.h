#pragma once
#ifndef HANABI_IMGUILAYER_H
#define HANABI_IMGUILAYER_H

#include "Layers/Layer.h"

namespace Hanabi {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event &e) override;
        virtual void OnImGuiRender() override;

        void Begin();
        void End();

        void BlockEvents(bool block) { m_BlockEvents = block; }

        void SetDarkThemeColors();

    private:
        bool m_BlockEvents = true;
    };
}

#endif