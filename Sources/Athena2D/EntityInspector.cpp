#include "EntityInspector.h"
#include <imgui.h>

#include "Rigidbody.h"
#include "Script.h"
#include "Sprite.h"

EntityInspector::EntityInspector(World* w)
{
    title = "Entity Inspector";
    world = w;
    width = 600.0f;
    height = 600.0f;
}

std::string selectedID;
void EntityInspector::renderPanel()
{
    if (isShowing()) {
        // Left
        {
            ImGui::BeginChild("left pane", ImVec2(150, 0), true);

            world->eachEntity([](std::shared_ptr<Entity> ent)
                {
                    if (selectedID.empty())
                        selectedID = ent->id;

                    if (ent) {
                        if (ImGui::Selectable(ent->id.c_str(), selectedID == ent->id))
                            selectedID = ent->id;
                    }
                });

            ImGui::EndChild();
        }
        ImGui::SameLine();

        // Right
        {
            ImGui::BeginGroup();
            ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
            ImGui::Text("Selected: %s", selectedID.c_str());
            ImGui::Separator();

            std::shared_ptr<Entity> ent = world->getEntity(selectedID);

            if (ent) {
                ImGui::Text("Position:");
                ImGui::DragFloat("X", &ent->pos.x, 1.0f);
                ImGui::DragFloat("Y", &ent->pos.y, 1.0f);
                ImGui::DragFloat("Rotation", &ent->rot, 1.0f);

                auto sprite = ent->getComponent<Sprite>();
                if (sprite && ImGui::CollapsingHeader("Sprite", ImGuiTreeNodeFlags_None))
                {
                    std::string layer = "";

                    switch (sprite->layer)
                    {
                    case SpriteLayer::BACKGROUND: layer = "BACKGROUND"; break;
                    case SpriteLayer::FOREGROUND: layer = "FOREGROUND"; break;
                    case SpriteLayer::CHARACTER:  layer = "CHARACTER"; break;
                    case SpriteLayer::UI:         layer = "UI"; break;
                    default:                      layer = "UNKNOWN";
                    }

                    ImGui::Text("Width:  %d", sprite->width);
                    ImGui::Text("Height: %d", sprite->height);
                    ImGui::Text("Source: %s", sprite->src.c_str());
                    ImGui::Text("Layer:  %s (%d)", layer.c_str(), sprite->layer);
                    ImGui::Text("Loaded: %s", sprite->loaded ? "true" : "false");
                }

                auto script = ent->getComponent<Script>();
                if (script && ImGui::CollapsingHeader("Script", ImGuiTreeNodeFlags_None))
                {
                    ImGui::Text("Source: %s", script->src.c_str());
                    ImGui::Text("Loaded: %s", script->loaded ? "true" : "false");
                }

                auto rb = ent->getComponent<Rigidbody>();
                if (rb && ImGui::CollapsingHeader("Rigidbody", ImGuiTreeNodeFlags_None))
                {
                    ImGui::Text("Width:  %d", rb->width);
                    ImGui::Text("Height: %d", rb->height);
                }
            }

            ImGui::EndChild();
            ImGui::EndGroup();
        }

        ImGui::End();
    }
}
