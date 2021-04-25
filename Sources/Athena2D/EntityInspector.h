#pragma once

#include "ImGuiTool.h"
#include "World.h"

class EntityInspector : public ImGuiTool {
public:
    EntityInspector(World* world);

protected:
    void renderPanel() override;

private:
    World* world;
};
