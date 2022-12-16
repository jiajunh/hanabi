#pragma once
#ifndef HANABI_MOUSEEVENT_H
#define HANABI_MOUSEEVENT_H

#include "Core/MouseCode.h"
#include "Events/Event.h"

namespace Hanabi {
    // Mouse move event
    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(const float x, const float y) : m_MouseX(x), m_MouseY(y) {}

        float GetX() const { return m_MouseX; }
        float GetY() const { return m_MouseY; }

        std::string ToString() const override {
            std::string s = "MouseMovedEvent: " + std::to_string(m_MouseX) + std::to_string(m_MouseY);
            return s;
        }

        EVENT_CLASS_TYPE(MouseMoved);
        EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryMouse);

    private:
        float m_MouseX, m_MouseY;
    };

    // Mouse scroll event
    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(const float xOffset, const float yOffset)
            : m_XOffset(xOffset), m_YOffset(yOffset) {}

        float GetXOffset() const { return m_XOffset; }
        float GetYOffset() const { return m_YOffset; }

        std::string ToString() const override {
            std::string ss;
            ss = "MouseScrolledEvent: " + std::to_string(GetXOffset()) + ", " + std::to_string(GetYOffset());
            return ss;
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    private:
        float m_XOffset, m_YOffset;
    };

    // Mouse button abstract class
    class MouseButtonEvent : public Event {
    public:
        MouseCode GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton)
    protected:
        MouseButtonEvent(const MouseCode button)
            : m_Button(button) {}

        MouseCode m_Button;
    };

    // mouse press event
    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(const MouseCode button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override {
            std::string ss = "MouseButtonPressedEvent: " + std::to_string(m_Button);
            return ss;
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    // mouse release event
    class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(const MouseCode button)
            : MouseButtonEvent(button) {}

        std::string ToString() const override {
            std::string ss = "MouseButtonPressedEvent: " + std::to_string(m_Button);
            return ss;
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}

#endif