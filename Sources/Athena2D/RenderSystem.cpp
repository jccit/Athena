#include "pch.h"
#include "RenderSystem.h"
#include "Sprite.h"
#include <Console/Console.h>
#include <SDL_image.h>
#include "ImGuiHelper.h"
#include <map>
#include <set>

SDL_Renderer* renderer;
ImGuiHelper* helper;
std::map<std::string, SDL_Texture*> textureCache;
uint64_t lastEntCount = 0;

RenderSystem::RenderSystem()
{
	ignorePause = true;
	helper = new ImGuiHelper();
}

RenderSystem::~RenderSystem()
{
	delete helper;
}

void RenderSystem::init(World* world)
{
	LOG("Init", "RenderSystem");
	
	win = new Window();
	renderer = win->getRenderer();

	helper->init(win, world);
	
	state = SystemState::ACTIVE;
}

void RenderSystem::shutdown()
{
	LOG("Shutdown", "RenderSystem");
	helper->shutdown();
	delete win;
}

void RenderSystem::preload(std::shared_ptr<Entity> entity, float deltaTime)
{
	if (entity) {
		std::shared_ptr<Sprite> sprite = entity->getComponent<Sprite>();

		if (sprite && !sprite->loaded && !sprite->failed)
		{
			sprite->texture = getCachedTexture(sprite->src);
			if (sprite->texture == nullptr)
			{
				LOG_ERROR("Failed to load texture " + sprite->src, "RenderSystem");
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
		}
	}
}

void RenderSystem::beforeUpdate(EntityList* entities, float deltaTime)
{	
	helper->newFrame(deltaTime, win);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void RenderSystem::update(EntityList* entities, float deltaTime)
{
	std::multimap<SpriteLayer, std::shared_ptr<Entity>> spriteOrder;

	for (auto [id, unsortedEnt]: *entities)
	{
		if (unsortedEnt) {
			std::shared_ptr<Sprite> sprite = unsortedEnt->getComponent<Sprite>();

			if (sprite)
			{
				spriteOrder.insert(std::pair(sprite->layer, unsortedEnt));
			}
		}
	}
	
	
	for (auto [layer, entity] : spriteOrder)
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
}

void RenderSystem::afterUpdate(EntityList* entities, float deltaTime)
{
	ImGuiHelper::render();
	SDL_RenderPresent(renderer);

	removeUnusedTextures(entities);
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

SDL_Texture* RenderSystem::getCachedTexture(std::string path)
{
	if (textureCache.count(path))
	{
		return textureCache[path];
	}
	
	LOG_VERBOSE("Loading sprite " + path, "RenderSystem");

	std::string fullPath = "sprites/" + path;
	SDL_Surface* imgSurface = IMG_Load(fullPath.c_str());
	if (imgSurface == nullptr)
	{
		LOG_ERROR("Failed to load sprite " + path, "RenderSystem");
		return nullptr;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, imgSurface);
	if (tex == nullptr)
	{
		LOG_ERROR("Failed to create hardware texture for " + path, "RenderSystem");
		return nullptr;
	}

	SDL_FreeSurface(imgSurface);

	textureCache[path] = tex;

	return tex;
}

void RenderSystem::removeUnusedTextures(EntityList* entities)
{
	if (entities->size() != lastEntCount)
	{
		std::set<std::string> textures;

		for (auto const& item : textureCache)
			textures.insert(item.first);

		for (auto [id, unsortedEnt] : *entities)
		{
			if (unsortedEnt) {
				std::shared_ptr<Sprite> sprite = unsortedEnt->getComponent<Sprite>();

				if (sprite)
				{
					if (textures.find(sprite->src) != textures.end())
					{
						textures.erase(sprite->src);
					}
				}
			}
		}

		// we have textures to remove!
		if (textures.size() > 0)
		{
			for (auto const tex : textures)
			{
				SDL_Texture* sdlTex = textureCache[tex];
				SDL_DestroyTexture(sdlTex);
				textureCache.erase(tex);
			}
		}

		lastEntCount = entities->size();
	}
}
