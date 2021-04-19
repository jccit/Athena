#include "pch.h"
#include "PerfMonitor.h"

PerfMonitor::PerfMonitor() = default;
PerfMonitor::PerfMonitor(int max)
{
	maxFrames = max;
}

void PerfMonitor::logFrameTime(float time)
{
	times.push_back(time);
	purgeFrames();
}

void PerfMonitor::setFrameCount(int count)
{
	maxFrames = count;
}

float PerfMonitor::getAvgFrameTime()
{
	size_t count = times.size();
	float timeTotal = 0.0f;

	for (auto time : times) {
		timeTotal += time;
	}

	return timeTotal / static_cast<float>(count);
}

float PerfMonitor::getFPS()
{
	return 1.0f / getAvgFrameTime();
}

void PerfMonitor::purgeFrames()
{
	while (times.size() > maxFrames) {
		times.pop_front();
	}
}
