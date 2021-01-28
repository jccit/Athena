#include "ImGuiConsole.h"
#include <imgui.h>
#include <iostream>
#include <SDL.h>
#include <Console/Console.h>

char inputBuf[256];
static void  Strtrim(char* s) { char* str_end = s + strlen(s); while (str_end > s && str_end[-1] == ' ') str_end--; *str_end = 0; }

ImGuiConsole::ImGuiConsole()
{
    title = "Console";
    shortcut = "~";
    scancode = SDL_SCANCODE_GRAVE;

    memset(inputBuf, 0, sizeof(inputBuf));

    LOG_VERBOSE("Created console window", "ImGuiConsole");
}

static int staticTextCallback(ImGuiInputTextCallbackData* data)
{
    ImGuiConsole* console = (ImGuiConsole*)data->UserData;
    return console->textCallback(data);
}

void ImGuiConsole::renderPanel()
{
    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Console", &showing))
    {
        ImGui::End();
        return;
    }

    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
	
    for (auto message : messages)
    {
        ImGui::TextUnformatted(message.c_str());
    }

    ImGui::PopStyleVar();
    ImGui::EndChild();
    ImGui::Separator();
    
    // Command-line
    bool reclaim_focus = false;
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
    if (ImGui::InputText("Input", inputBuf, IM_ARRAYSIZE(inputBuf), input_text_flags, &staticTextCallback, (void*)this))
    {
        char* s = inputBuf;
        Strtrim(s);
        if (s[0])
            runCommand(s);
        strcpy_s(s, 256, "");
        reclaim_focus = true;
    }

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

    ImGui::End();
}

int ImGuiConsole::textCallback(ImGuiInputTextCallbackData* data)
{
	switch (data->EventFlag)
	{
    case ImGuiInputTextFlags_CallbackCompletion:
        // TODO: Add completion
        break;
    case ImGuiInputTextFlags_CallbackHistory:
        // TODO: Add history
        break;
	}
    return 0;
}

void ImGuiConsole::runCommand(std::string command)
{
    messages.push_back("> " + command);
    Console::getInstance().exec(command);
}

void ImGuiConsole::onPrint(std::string text, std::string source, OutputLevel level)
{
    std::string prefix = levelToString(level);
	messages.push_back(prefix + "/" + source + ": " + text);
}
