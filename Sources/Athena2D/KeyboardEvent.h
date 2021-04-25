#pragma once

#include "Event.h"

class KeyboardEvent : public Event {
public:
    KeyboardEvent(std::string name, bool down)
    {
        keyName = name;
        isDown = down;
    }

    std::string keyName;
    bool isDown;
};
