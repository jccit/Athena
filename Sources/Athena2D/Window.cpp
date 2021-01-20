#include "Window.h"

Window::Window()
{
	win = SDL_CreateWindow("Foundation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
}

Window::~Window()
{
	if (win) SDL_DestroyWindow(win);
	if (renderer) SDL_DestroyRenderer(renderer);
}

SDL_Renderer* Window::getRenderer()
{
	if (!renderer)
		renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	return renderer;
}
