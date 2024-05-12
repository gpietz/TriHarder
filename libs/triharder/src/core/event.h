#pragma once

namespace TriHarder {
    enum class EventType {
        Quit,
        KeyPress,
        KeyReleased,
        MouseMove,
        MouseScroll,
        MouseEnter,
        MouseLeave,
        MouseClick,
    };

    class Event {
    public:
        explicit Event(EventType type) : type_(type) {}
        virtual ~Event() {};

        EventType getType() const { return type_; }

    private:
        EventType type_;
    };

    class KeyEvent : public Event {
    public:
        KeyEvent(EventType type, int keycode) : Event(type), keycode_(keycode) {}

        int getKeyCode() const { return keycode_; }

    private:
        int keycode_;
    };

    class KeyPressedEvent : public KeyEvent {
        KeyPressedEvent(int keycode) : KeyEvent(EventType::KeyPress, keycode) {}
    };

    class KeyReleasedEvent : public KeyEvent {
        KeyReleasedEvent(int keycode) : KeyEvent(EventType::KeyPress, keycode) {}
    };
}
