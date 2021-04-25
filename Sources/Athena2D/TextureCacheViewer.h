#pragma once

#include "ImGuiTool.h"

#include <map>
#include <string>

class TextureCacheViewer : public ImGuiTool {
public:
    TextureCacheViewer(std::map<std::string, SDL_Texture*>* texCache);

protected:
    void renderPanel() override;

private:
    std::map<std::string, SDL_Texture*>* cache;
};
