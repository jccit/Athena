#pragma once

#include "Window.h"

class ImGuiHelper
{
public:
	static void init(Window* win);
	static void shutdown();
	static void newFrame(float delta, Window* win);
	static void render();

	static bool wantsKeyboard();
};

