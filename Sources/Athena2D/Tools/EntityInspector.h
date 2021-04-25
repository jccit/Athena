#pragma once

#include "DevTool.h"
#include "World.h"

class EntityInspector : public DevTool {
public:
    EntityInspector(World* world);

protected:
    void renderPanel() override;

private:
    World* world;
};
