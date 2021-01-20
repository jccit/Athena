#include "Engine.h"
#include "Window.h"
#include "SqVM.h"
#include <SDL.h>

SqVM* sq;
Window* window;

int Engine::init()
{
	SDL_Init(SDL_INIT_VIDEO);
	window = new Window();
	sq = new SqVM();

	sq->runScript("test.nut");

	return 0;
}

void Engine::shutdown()
{
	delete window;
	delete sq;

	SDL_Quit();
}

void Engine::loop()
{
	bool running = true;
	SDL_Event e;
	SDL_Renderer* renderer = window->getRenderer();

	while (running)
	{
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				running = false;
			}
		}

		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);
	}
}
