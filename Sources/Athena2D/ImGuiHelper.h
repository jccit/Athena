#pragma once

#include "Tools/DevTool.h"
#include "Window.h"

class World;

class ImGuiHelper {
public:
    ImGuiHelper();
    ~ImGuiHelper();

    void init(Window* win, World* w);
    void shutdown();
    void newFrame(float delta, Window* win);
    void addTool(std::shared_ptr<DevTool> tool);

    static void render();
    static bool wantsKeyboard();
    static bool wantsMouse();

private:
    World* world;
};
