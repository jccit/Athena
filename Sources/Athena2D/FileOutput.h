#pragma once

#include <Console/IOutput.h>
#include <fstream>

class FileOutput : public IOutput {
public:
    FileOutput();
    ~FileOutput();

    void onPrint(std::string text, std::string source, OutputLevel level) override;

private:
    std::ofstream logFile;
    std::string filePath;
};
