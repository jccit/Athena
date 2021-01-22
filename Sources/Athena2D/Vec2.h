#pragma once

struct Vec2
{
	Vec2()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	
	Vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float x;
	float y;
};
