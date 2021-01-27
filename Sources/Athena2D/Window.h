#pragma once

#include <memory>
#include <SDL.h>

class Window
{
public:
	Window();
	~Window();

	SDL_Renderer* getRenderer();

	int getWidth();
	int getHeight();

	SDL_Window* getSDLWindow();

private:
	SDL_Window* win = nullptr;
	SDL_Renderer* renderer = nullptr;
};

