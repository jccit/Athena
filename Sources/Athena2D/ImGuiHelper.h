#pragma once

#include "Window.h"
#include "ImGuiConsole.h"

class ImGuiHelper
{
public:
	ImGuiHelper();
	~ImGuiHelper();
	
	static void init(Window* win);
	static void shutdown();
	void newFrame(float delta, Window* win);
	static void render();

	static bool wantsKeyboard();
};

