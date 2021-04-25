#include "pch.h"

#include "StdOutput.h"

#include <iostream>

StdOutput::StdOutput() = default;
StdOutput::~StdOutput() = default;

void StdOutput::onPrint(std::string text, std::string source, OutputLevel level)
{
    std::string prefix = levelToString(level);

    std::cout << prefix << "/" << source << ": " << text << std::endl;
}
