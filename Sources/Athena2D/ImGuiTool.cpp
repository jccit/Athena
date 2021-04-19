#include "ImGuiTool.h"
#include <imgui.h>

void ImGuiTool::toggle()
{
	showing = !showing;
}

void ImGuiTool::render()
{
	if (ImGui::IsKeyPressed(scancode))
	{
		toggle();
	}

	if (showing)
	{
		renderPanel();
	}
}

bool ImGuiTool::isShowing()
{
	ImGui::SetNextWindowSize(ImVec2(width, height), ImGuiCond_FirstUseEver);
	if (!ImGui::Begin(title, &showing))
	{
		ImGui::End();
		return false;
	}

	return true;
}

void ImGuiTool::renderMenu()
{
	ImGui::MenuItem(title, shortcut, &showing);
}
