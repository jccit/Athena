#pragma once

#include "DevTool.h"
#include <Console/IOutput.h>
#include <imgui.h>
#include <vector>

class DevConsole : public IOutput, public DevTool {
public:
    DevConsole();

    void onPrint(std::string text, std::string source, OutputLevel level) override;
    int textCallback(ImGuiInputTextCallbackData* data);

protected:
    void renderPanel() override;

private:
    void runCommand(std::string command);

    std::vector<std::string> messages;
};
