#pragma once

#include "../Event.h"

class MouseButtonEvent : public Event {
public:
    MouseButtonEvent(int button, bool down)
    {
        this->button = button;
        this->down = down;
    }

    int button;
    bool down;
};
