#include "pch.h"
#include "Window.h"
#include <Console/Console.h>
#include <Console/CVar.h>

CVar width = CVar("r_width", 800, CVAR_PERSIST);
CVar height = CVar("r_height", 600, CVAR_PERSIST);
CVar fullscreen = CVar("r_fullscreen", false, CVAR_PERSIST);
CVar borderless = CVar("r_borderless", false, CVAR_PERSIST);
CVar vsync = CVar("r_vsync", false, CVAR_PERSIST);

Window::Window()
{
	Uint32 winFlags = 0;

	if (fullscreen.getBool() && !borderless.getBool())
	{
		winFlags |= SDL_WINDOW_FULLSCREEN;
	}
	else if (fullscreen.getBool() && borderless.getBool())
	{
		winFlags |= SDL_WINDOW_BORDERLESS;
	}
	
	win = SDL_CreateWindow("Foundation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width.getInt(), height.getInt(), winFlags);
	LOG("Created window " + width.get() + "x" + height.get(), "Window");
}

Window::~Window()
{
	if (win) SDL_DestroyWindow(win);
	if (renderer) SDL_DestroyRenderer(renderer);

	LOG("Destroyed", "Window");
}

SDL_Renderer* Window::getRenderer()
{
	if (!renderer) {
		Uint32 renderFlags = SDL_RENDERER_ACCELERATED;

		if (vsync.getBool())
		{
			renderFlags |= SDL_RENDERER_PRESENTVSYNC;
		}
		
		renderer = SDL_CreateRenderer(win, -1, renderFlags);
		LOG("Created accelerated renderer", "Window");
	}

	return renderer;
}
