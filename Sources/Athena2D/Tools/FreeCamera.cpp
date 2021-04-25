#include "pch.h"

#include "FreeCamera.h"

#include <imgui.h>

FreeCamera::FreeCamera(Camera* cam)
{
    title = "Free Camera";
    camera = cam;
    width = 200;
    height = 100;
}

void FreeCamera::renderPanel()
{
    if (isShowing()) {
        if (ImGui::Button("Toggle Free Cam")) {
            enabled = !enabled;
            camera->isFreeCam = enabled;

            if (enabled) {
                // Save last pos
                lastPos = camera->position;
            } else {
                // Restore pos
                camera->position = lastPos;
            }
        }

        if (enabled) {
            ImGui::DragFloat("X", &camera->position.x, 1.0f);
            ImGui::DragFloat("Y", &camera->position.y, 1.0f);
        } else {
            ImGui::Text("X: %.3f", camera->position.x);
            ImGui::Text("Y: %.3f", camera->position.y);
        }

        ImGui::End();
    }
}
