#pragma once

#include "Component.h"
#include <SDL.h>

struct Sprite : Component
{
	std::string src;
	SDL_Texture* texture;

	int width = 0;
	int height = 0;
	
	bool loaded = false;
};