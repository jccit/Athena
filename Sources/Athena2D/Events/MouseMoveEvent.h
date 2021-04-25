#pragma once

#include "../Event.h"

class MouseMoveEvent : public Event {
public:
    MouseMoveEvent(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    int x;
    int y;
};
