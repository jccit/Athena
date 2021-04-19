#include "PerfOverlay.h"

#include <imgui.h>

PerfOverlay::PerfOverlay()
{
}

void PerfOverlay::render(bool hasMenu)
{
    const float padding = 5.0f;
    ImGuiIO& io = ImGui::GetIO();
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove;
   
    ImVec2 window_pos = ImVec2(io.DisplaySize.x - padding, hasMenu ? 19.0f + padding : padding);
    ImVec2 window_pos_pivot = ImVec2(1.0f, 0.0f);
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    if (ImGui::Begin("Example: Simple overlay", NULL, window_flags))
    {
        ImGui::Text("Simple overlay\n" "in the corner of the screen.\n" "(right-click to change position)");
        ImGui::Separator();
        ImGui::Text("Frame time: (%.5f, %.5f)", io.DeltaTime, 1.0f / io.DeltaTime);
    }
    ImGui::End();
}
