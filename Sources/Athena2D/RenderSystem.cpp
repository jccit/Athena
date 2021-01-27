#include "pch.h"
#include "RenderSystem.h"
#include "Sprite.h"
#include <Console/Console.h>
#include <SDL_image.h>
#include "ImGuiHelper.h"

SDL_Renderer* renderer;
ImGuiHelper* helper;

RenderSystem::RenderSystem()
{
	ignorePause = true;
	helper = new ImGuiHelper();
}

RenderSystem::~RenderSystem()
{
	delete helper;
}

void RenderSystem::init()
{
	LOG("Init", "RenderSystem");
	
	win = new Window();
	renderer = win->getRenderer();

	ImGuiHelper::init(win);
	
	state = SystemState::ACTIVE;
}

void RenderSystem::shutdown()
{
	LOG("Shutdown", "RenderSystem");
	ImGuiHelper::shutdown();
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

void RenderSystem::beforeUpdate(EntityList* entities, float deltaTime)
{	
	helper->newFrame(deltaTime, win);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void RenderSystem::update(std::shared_ptr<Entity> entity, float deltaTime)
{
	std::shared_ptr<Sprite> sprite = entity->getComponent<Sprite>();

	if (sprite && sprite->loaded && !sprite->failed)
	{
		SDL_Rect dst = {
			static_cast<int>(entity->pos.x),
			static_cast<int>(entity->pos.y),
			sprite->width,
			sprite->height
		};

		if (entity->rot != 0)
		{
			SDL_Point centre;
			if (entity->origin.isZero())
			{
				centre = entity->origin.toPoint();
			}
			
			SDL_RenderCopyEx(renderer, sprite->texture, NULL, &dst, entity->rot, entity->origin.isZero() ? NULL : &centre, SDL_FLIP_NONE);
		}
		else
		{
			SDL_RenderCopy(renderer, sprite->texture, NULL, &dst);
		}
	}
}

void RenderSystem::afterUpdate(EntityList* entities, float deltaTime)
{
	ImGuiHelper::render();
	SDL_RenderPresent(renderer);
}

void RenderSystem::beforeFixedUpdate(EntityList* entities, float deltaTime)
{
}

void RenderSystem::fixedUpdate(std::shared_ptr<Entity> entity, float deltaTime)
{
}

void RenderSystem::afterFixedUpdate(EntityList* entities, float deltaTime)
{
}
