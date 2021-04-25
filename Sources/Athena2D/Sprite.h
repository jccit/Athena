#pragma once

#include "CerealArchive.h"
#include "Component.h"

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/string.hpp>

enum class SpriteLayer : int8_t {
    BACKGROUND = -100,
    FOREGROUND = 0,
    CHARACTER = 50,
    UI = 100
};

struct Sprite final : public Component {
    std::string src;
    SpriteLayer layer;
    SDL_Texture* texture;

    int width = 0;
    int height = 0;

    bool loaded = false;
    bool failed = false;

    std::string toString() override
    {
        return src;
    }

    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(CEREAL_NVP(src), CEREAL_NVP(layer));
    }
};

CEREAL_REGISTER_TYPE(Sprite);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Sprite);