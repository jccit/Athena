#include "RenderSystem.h"
#include "Sprite.h"
#include <Console/Console.h>
#include <SDL.h>
#include <SDL_image.h>

SDL_Renderer* renderer;

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::init()
{
	win = new Window();
	renderer = win->getRenderer();
	
	state = SystemState::ACTIVE;
}

void RenderSystem::shutdown()
{
	delete win;
}

void RenderSystem::preload(std::shared_ptr<Entity> entity, double deltaTime)
{
	std::shared_ptr<Sprite> sprite = entity->getComponent<Sprite>();

	if (!sprite->loaded)
	{
		std::string path = "sprites/" + sprite->src;
		SDL_Surface* imgSurface = IMG_Load(path.c_str());
		sprite->texture = SDL_CreateTextureFromSurface(renderer, imgSurface);
		SDL_QueryTexture(sprite->texture, nullptr, nullptr, &sprite->width, &sprite->height);
		
		sprite->loaded = true;
		SDL_FreeSurface(imgSurface);
	}
}

void RenderSystem::beforeUpdate(double deltaTime)
{
	SDL_RenderClear(renderer);
}

void RenderSystem::update(std::shared_ptr<Entity> entity, double deltaTime)
{
	std::shared_ptr<Sprite> sprite = entity->getComponent<Sprite>();

	if (sprite->loaded)
	{
		SDL_Rect dst = { entity->pos.x, entity->pos.y, sprite->width, sprite->height };
		SDL_RenderCopy(renderer, sprite->texture, NULL, &dst);
	}
}

void RenderSystem::afterUpdate(double deltaTime)
{
	SDL_RenderPresent(renderer);
}
