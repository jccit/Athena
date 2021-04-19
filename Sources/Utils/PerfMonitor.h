#pragma once

#include <deque>

class PerfMonitor
{
public:
	PerfMonitor();
	PerfMonitor(int max);

	void logFrameTime(float time);
	void setFrameCount(int count);

	float getAvgFrameTime();
	float getFPS();

private:
	std::deque<float> times;
	int maxFrames = 10;

	void purgeFrames();
};