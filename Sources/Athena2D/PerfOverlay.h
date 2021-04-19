#pragma once

class PerfOverlay
{
public:
	PerfOverlay();

	void render(bool hasMenu);

private:
	float ftCounter = 0.0f;

	float lastFPS = 0.0f;
	float lastFT = 0.0f;
};

