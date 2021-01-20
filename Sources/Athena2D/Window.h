#pragma once

#include <memory>
#include <SDL.h>

class Window
{
public:
	Window();
	~Window();

	SDL_Renderer* getRenderer();

private:
	SDL_Window* win = nullptr;
	SDL_Renderer* renderer = nullptr;
};

