#include "pch.h"

#include "DevConsole.h"

#include <iostream>

#include <imgui.h>

char inputBuf[256];
static void Strtrim(char* s)
{
    char* str_end = s + strlen(s);
    while (str_end > s && str_end[-1] == ' ')
        str_end--;
    *str_end = 0;
}

DevConsole::DevConsole()
{
    title = "Console";
    shortcut = "~";
    scancode = SDL_SCANCODE_GRAVE;
    width = 520.0f;
    height = 600.0f;

    memset(inputBuf, 0, sizeof(inputBuf));

    LOG_VERBOSE("Created console window", "DevConsole");
}

static int staticTextCallback(ImGuiInputTextCallbackData* data)
{
    DevConsole* console = (DevConsole*)data->UserData;
    return console->textCallback(data);
}

void DevConsole::renderPanel()
{
    if (isShowing()) {
        const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing

        for (auto message : messages) {
            ImGui::TextUnformatted(message.c_str());
        }

        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::Separator();

        // Command-line
        bool reclaim_focus = false;
        ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
        if (ImGui::InputText("Input", inputBuf, IM_ARRAYSIZE(inputBuf), input_text_flags, &staticTextCallback, (void*)this)) {
            char* s = inputBuf;
            Strtrim(s);
            if (s[0])
                runCommand(s);
#ifdef _WIN32
            strcpy_s(s, 256, "");
#else
            strcpy(s, "");
#endif
            reclaim_focus = true;
        }

        // Auto-focus on window apparition
        ImGui::SetItemDefaultFocus();
        if (reclaim_focus)
            ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

        ImGui::End();
    }
}

int DevConsole::textCallback(ImGuiInputTextCallbackData* data)
{
    std::string input = std::string(data->Buf, data->BufTextLen);

    switch (data->EventFlag) {
    case ImGuiInputTextFlags_CallbackCompletion:
        // TODO: Add completion
        {
            std::vector<std::string> completions = Console::getInstance().autocomplete(input);
            if (completions.size() > 0) {
                data->DeleteChars(0, data->CursorPos);
                data->InsertChars(data->CursorPos, completions[0].c_str());
                data->InsertChars(data->CursorPos, " ");
            }
        }
        break;
    case ImGuiInputTextFlags_CallbackHistory:
        // TODO: Add history
        break;
    }
    return 0;
}

void DevConsole::runCommand(std::string command)
{
    messages.push_back("> " + command);
    Console::getInstance().exec(command);
}

void DevConsole::onPrint(std::string text, std::string source, OutputLevel level)
{
    std::string prefix = levelToString(level);
    messages.push_back(prefix + "/" + source + ": " + text);
}
