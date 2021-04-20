#pragma once

#include "ImGuiTool.h"
#include "Camera.h"

class FreeCamera : public ImGuiTool
{
public:
	FreeCamera(Camera* cam);

protected:
	void renderPanel() override;

private:
	Camera* camera;
	bool enabled = false;
	Vec2 lastPos;
};

