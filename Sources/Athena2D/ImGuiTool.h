#pragma once

class ImGuiTool
{
public:
	void render();
	void renderMenu();
	
	void toggle();

	bool showing = false;

protected:
	virtual void renderPanel() = 0;
	
	const char* title = "Tool";
	const char* shortcut = 0;
	int scancode = -1;
};