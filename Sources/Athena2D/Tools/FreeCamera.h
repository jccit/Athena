#pragma once

#include "../Camera.h"
#include "DevTool.h"

class FreeCamera : public DevTool {
public:
    FreeCamera(Camera* cam);

protected:
    void renderPanel() override;

private:
    Camera* camera;
    bool enabled = false;
    Vec2 lastPos;
};
