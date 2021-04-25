#pragma once

#ifdef PHYSICS

#include "../CerealArchive.h"
#include "../Component.h"
#include "../Vec2.h"

#include <box2d/b2_body.h>
#include <cereal/types/polymorphic.hpp>

struct Rigidbody final : public Component {
    int width = 0;
    int height = 0;
    b2BodyType type = b2_dynamicBody;

    b2Body* body;

    // Used for calculating static obj velocity
    Vec2 lastPos;

    std::string toString() override
    {
        return "rigidbody";
    }

    template <class Archive>
    void serialize(Archive& ar)
    {
        ar(CEREAL_NVP(width), CEREAL_NVP(height), CEREAL_NVP(type));
    }
};

CEREAL_REGISTER_TYPE(Rigidbody);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Rigidbody);
#endif