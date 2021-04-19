#include "TextureCacheViewer.h"
#include <imgui.h>
#include <string>

TextureCacheViewer::TextureCacheViewer(std::map<std::string, SDL_Texture*>* texCache)
{
	title = "Texture Cache Viewer";
    cache = texCache;
}

std::string selectedTexture;
void TextureCacheViewer::renderPanel()
{
	if (isShowing()) {
        // left
        {
            ImGui::BeginChild("items", ImVec2(200, 0), true);

            for (auto& cacheEntry : *cache) {
                if (selectedTexture.empty()) {
                    selectedTexture = cacheEntry.first;
                }

                if (ImGui::Selectable(cacheEntry.first.c_str(), selectedTexture == cacheEntry.first))
                    selectedTexture = cacheEntry.first;

            }

            ImGui::EndChild();
        }

        ImGui::SameLine();

        // right
        {
            ImGui::BeginChild("item view", ImVec2(0, 0));

            if (cache->count(selectedTexture)) {
                SDL_Texture* tex = cache->at(selectedTexture);
                int texWidth = 0;
                int texHeight = 0;
                SDL_QueryTexture(tex, nullptr, nullptr, &texWidth, &texHeight);
                ImGui::Image((ImTextureID)tex, ImVec2(texWidth, texHeight));
            }

            ImGui::EndChild();
        }

        ImGui::End();
	}
}
