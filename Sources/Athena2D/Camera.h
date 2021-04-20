#pragma once

#include "Vec2.h"

class Camera
{
public:
	Camera();

	Vec2 getPosition();
	void setPosition(Vec2 newPos);
	void setPosition(int x, int y);

	Vec2 position;
	bool isFreeCam = false;
};

