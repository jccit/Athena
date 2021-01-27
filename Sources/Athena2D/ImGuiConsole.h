#pragma once

#include <vector>
#include <Console/IOutput.h>
#include <imgui.h>
#include "ImGuiTool.h"

class ImGuiConsole : public IOutput, public ImGuiTool
{
public:
	ImGuiConsole();
	
	void onPrint(std::string text, std::string source, OutputLevel level) override;
	int textCallback(ImGuiInputTextCallbackData* data);

protected:
	void renderPanel() override;

private:
	void runCommand(std::string command);
	
	std::vector<std::string> messages;
};
