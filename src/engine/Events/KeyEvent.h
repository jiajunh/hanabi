#pragma once
#ifndef HANABI_KEYEVENT_H
#define HANABI_KEYEVENT_H

#include "Core/KeyCode.h"
#include "Events/Event.h"

namespace Hanabi {
    // Abstract key event
    class KeyEvent : public Event {
    public:
        KeyCode GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
    protected:
        KeyEvent(const KeyCode keycode) : m_KeyCode(keycode) {}
        KeyCode m_KeyCode;
    };

    // Press key event
    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(const KeyCode keycode, bool isRepeat = false)
            : KeyEvent(keycode), m_IsRepeat(isRepeat) {}

        bool IsRepeat() const { return m_IsRepeat; }

        std::string ToString() const override {
            std::string ss;
            ss = "KeyPressedEvent: " + std::to_string(m_KeyCode) + " (repeat = " + std::to_string(m_IsRepeat) + ")";
            return ss;
        }

        EVENT_CLASS_TYPE(KeyPressed)
    private:
        bool m_IsRepeat;
    };

    // Release key event
    class KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(const KeyCode keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override {
            std::string ss = "KeyReleasedEvent: " + std::to_string(m_KeyCode);
            return ss;
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    // key typed event
    class KeyTypedEvent : public KeyEvent {
    public:
        KeyTypedEvent(const KeyCode keycode)
            : KeyEvent(keycode) {}

        std::string ToString() const override {
            std::string ss = "KeyTypedEvent: " + std::to_string(m_KeyCode);
            return ss;
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}

#endif