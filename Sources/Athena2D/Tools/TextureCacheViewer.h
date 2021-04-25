#pragma once

#include "DevTool.h"

#include <map>
#include <string>

class TextureCacheViewer : public DevTool {
public:
    TextureCacheViewer(std::map<std::string, SDL_Texture*>* texCache);

protected:
    void renderPanel() override;

private:
    std::map<std::string, SDL_Texture*>* cache;
};
