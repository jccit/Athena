#include "pch.h"

#include "DevTool.h"

#include <imgui.h>

void DevTool::toggle()
{
    showing = !showing;
}

void DevTool::handleInput()
{
    if (ImGui::IsKeyPressed(scancode)) {
        toggle();
    }
}

void DevTool::render()
{
    if (showing) {
        renderPanel();
    }
}

bool DevTool::isShowing()
{
    ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(title, &showing)) {
        ImGui::End();
        return false;
    }

    return true;
}

void DevTool::renderMenu()
{
    ImGui::MenuItem(title, shortcut, &showing);
}
