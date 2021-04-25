#pragma once

#include <Console/IOutput.h>

class StdOutput : public IOutput {
public:
    StdOutput();
    ~StdOutput();

    void onPrint(std::string text, std::string source, OutputLevel level) override;
};
