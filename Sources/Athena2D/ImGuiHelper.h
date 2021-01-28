#pragma once

#include "Window.h"
#include "ImGuiConsole.h"

class World;

class ImGuiHelper
{
public:
	ImGuiHelper();
	~ImGuiHelper();
	
	void init(Window* win, World* w);
	void shutdown();
	void newFrame(float delta, Window* win);
	static void render();

	static bool wantsKeyboard();

private:
	World* world;
};

