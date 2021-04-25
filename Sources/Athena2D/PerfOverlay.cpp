#include "pch.h"

#include "PerfOverlay.h"

#include <Utils/PerfMonitor.h>
#include <imgui.h>

CVar updateTime = CVar("perf_update", 0.1f, CVAR_PERSIST, "Interval between perf stats update");

PerfMonitor perfMon(120);

PerfOverlay::PerfOverlay()
{
}

void PerfOverlay::render(bool hasMenu)
{
    ImGuiIO& io = ImGui::GetIO();

    // Log frame time
    perfMon.logFrameTime(io.DeltaTime);
    ftCounter += io.DeltaTime;

    // Recalc stats after time
    if (ftCounter > updateTime.getFloat()) {
        ftCounter = 0;
        lastFPS = perfMon.getFPS();
        lastFT = perfMon.getAvgFrameTime() * 1000.0f;
    }

    const float padding = 5.0f;
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | ImGuiWindowFlags_NoMove;

    ImVec2 window_pos = ImVec2(io.DisplaySize.x - padding, hasMenu ? 19.0f + padding : padding);
    ImVec2 window_pos_pivot = ImVec2(1.0f, 0.0f);
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);

    ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
    if (ImGui::Begin("Performance", NULL, window_flags)) {
        ImGui::Text("Avg FPS: %.0f", lastFPS);
        ImGui::Text("Avg frame time: %.2fms", lastFT);
    }
    ImGui::End();
}
