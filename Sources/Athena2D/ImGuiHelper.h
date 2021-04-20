#pragma once

#include "Window.h"
#include "ImGuiTool.h"

class World;

class ImGuiHelper
{
public:
	ImGuiHelper();
	~ImGuiHelper();
	
	void init(Window* win, World* w);
	void shutdown();
	void newFrame(float delta, Window* win);
	void addTool(std::shared_ptr<ImGuiTool> tool);

	static void render();
	static bool wantsKeyboard();
	static bool wantsMouse();

private:
	World* world;
};

