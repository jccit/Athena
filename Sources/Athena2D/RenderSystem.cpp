#include "RenderSystem.h"
#include "Sprite.h"
#include <Console/Console.h>
#include <SDL.h>
#include <SDL_image.h>

SDL_Renderer* renderer;

RenderSystem::RenderSystem()
{
}

RenderSystem::~RenderSystem() = default;

void RenderSystem::init()
{
	LOG("Init", "RenderSystem");
	
	win = new Window();
	renderer = win->getRenderer();
	
	state = SystemState::ACTIVE;
}

void RenderSystem::shutdown()
{
	LOG("Shutdown", "RenderSystem");
	delete win;
}

void RenderSystem::preload(std::shared_ptr<Entity> entity, float deltaTime)
{
	std::shared_ptr<Sprite> sprite = entity->getComponent<Sprite>();

	if (sprite && !sprite->loaded && !sprite->failed)
	{
		LOG_VERBOSE("Loading sprite " + sprite->src, "RenderSystem");
		
		std::string path = "sprites/" + sprite->src;
		SDL_Surface* imgSurface = IMG_Load(path.c_str());
		if (imgSurface == nullptr)
		{
			LOG_ERROR("Failed to load sprite " + sprite->src, "RenderSystem");
			sprite->failed = true;
			return;
		}
		
		sprite->texture = SDL_CreateTextureFromSurface(renderer, imgSurface);
		if (sprite->texture == nullptr)
		{
			LOG_ERROR("Failed to create hardware texture for " + sprite->src, "RenderSystem");
			sprite->failed = true;
			return;
		}
		
		int queryRes = SDL_QueryTexture(sprite->texture, nullptr, nullptr, &sprite->width, &sprite->height);
		if (queryRes != 0)
		{
			LOG_ERROR("Error querying texture data for " + sprite->src, "RenderSystem");
			sprite->failed = true;
			return;
		}
		
		sprite->loaded = true;
		SDL_FreeSurface(imgSurface);
	}
}

void RenderSystem::beforeUpdate(float deltaTime)
{
	SDL_RenderClear(renderer);
}

void RenderSystem::update(std::shared_ptr<Entity> entity, float deltaTime)
{
	std::shared_ptr<Sprite> sprite = entity->getComponent<Sprite>();

	if (sprite && sprite->loaded && !sprite->failed)
	{
		SDL_Rect dst = { entity->pos.x, entity->pos.y, sprite->width, sprite->height };
		SDL_RenderCopy(renderer, sprite->texture, NULL, &dst);
	}
}

void RenderSystem::afterUpdate(float deltaTime)
{
	SDL_RenderPresent(renderer);
}
