#include "pch.h"
#include "BootParams.h"
#include "Window.h"
#include "SqVM.h"
#include <Console/Console.h>
#include <Console/CVar.h>

CVar width = CVar("r_width", 800, CVAR_PERSIST, "Width of the game window");
CVar height = CVar("r_height", 600, CVAR_PERSIST, "Height of the game window");
CVar fullscreen = CVar("r_fullscreen", false, CVAR_PERSIST, "0 for windowed, 1 for fullscreen mode");
CVar borderless = CVar("r_borderless", false, CVAR_PERSIST, "1 to enable borderless window mode, set r_fullscreen to 0");
CVar vsync = CVar("r_vsync", false, CVAR_PERSIST, "1 to enable vsync");
CVar software = CVar("r_software", false, CVAR_PERSIST, "1 to enable software rendering");

Window::Window()
{
	// BUG: SDL's D3D renderer is not clearing correctly when using imgui, set to opengl for now
#ifdef _WIN32
	if (g_devMode) {
		SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	}
#endif
	Uint32 winFlags = 0;

	if (!software.getBool())
		winFlags |= SDL_WINDOW_OPENGL;
	if (fullscreen.getBool() && !borderless.getBool())
		winFlags |= SDL_WINDOW_FULLSCREEN;
	else if (fullscreen.getBool() && borderless.getBool())
		winFlags |= SDL_WINDOW_BORDERLESS;
	
	win = SDL_CreateWindow("Foundation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width.getInt(), height.getInt(), winFlags);
	LOG("Created window " + width.get() + "x" + height.get(), "Window");

	updateSize();
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
		Uint32 renderFlags = 0;

		if (software.getBool())
			renderFlags |= SDL_RENDERER_SOFTWARE;
		else
			renderFlags |= SDL_RENDERER_ACCELERATED;

		if (vsync.getBool())
			renderFlags |= SDL_RENDERER_PRESENTVSYNC;
		
		renderer = SDL_CreateRenderer(win, -1, renderFlags);
		SDL_RendererInfo info;
		int res = SDL_GetRendererInfo(renderer, &info);
		const char* err = SDL_GetError();

		if (res != 0 || renderer == nullptr)
		{
			LOG_ERROR("Error creating renderer" + std::string(SDL_GetError()), "Window");
			return renderer;
		}

		
		LOG("Created accelerated " + std::string(info.name) +  " renderer", "Window");
	}

	return renderer;
}

int Window::getWidth()
{
	return width.getInt();
}

int Window::getHeight()
{
	return height.getInt();
}

SDL_Window* Window::getSDLWindow()
{
	return win;
}

void Window::updateSize()
{
	SqVM::getInstance().exec("::screen <- { width = " + std::to_string(getWidth()) + ", height = " + std::to_string(getHeight()) + " }");
}
