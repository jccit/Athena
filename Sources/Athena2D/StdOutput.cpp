#include "pch.h"
#include "StdOutput.h"
#include <iostream>

StdOutput::StdOutput() = default;
StdOutput::~StdOutput() = default;

void StdOutput::onPrint(std::string text, std::string source, OutputLevel level)
{
	std::string prefix;

	switch (level)
	{
	case LEVEL_FATAL:
		prefix = "F";
		break;
	case LEVEL_ERROR:
		prefix = "E";
		break;
	case LEVEL_WARNING:
		prefix = "W";
		break;
	case LEVEL_DEBUG:
		prefix = "D";
		break;
	case LEVEL_VERBOSE:
		prefix = "V";
		break;
	case LEVEL_INFO:
		prefix = "I";
		break;
	}

	std::cout << prefix << "/" << source << ": " << text << std::endl;
}
