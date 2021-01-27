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

void ImGuiTool::renderMenu()
{
	ImGui::MenuItem(title, shortcut, &showing);
}
