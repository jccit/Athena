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
	bool isShowing();
	
	const char* title = "Tool";
	const char* shortcut = 0;
	int scancode = -1;
	float width = 600.0f;
	float height = 600.0f;
};