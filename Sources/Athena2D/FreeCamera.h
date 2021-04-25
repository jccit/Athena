#pragma once

#include "Camera.h"
#include "ImGuiTool.h"

class FreeCamera : public ImGuiTool {
public:
    FreeCamera(Camera* cam);

protected:
    void renderPanel() override;

private:
    Camera* camera;
    bool enabled = false;
    Vec2 lastPos;
};
