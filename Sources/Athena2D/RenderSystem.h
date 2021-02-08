#pragma once

#include "System.h"
#include "Window.h"

class RenderSystem final : public System
{
public:
	RenderSystem();
	virtual ~RenderSystem();

	void init(World* world) override;
	void shutdown() override;

	void preload(std::shared_ptr<Entity> entity, float deltaTime) override;
	void beforeUpdate(EntityList* entities, float deltaTime) override;
	void update(EntityList* entities, float deltaTime) override;
	void afterUpdate(EntityList* entities, float deltaTime) override;

	void beforeFixedUpdate(EntityList* entities, float deltaTime) override;
	void fixedUpdate(std::shared_ptr<Entity> entity, float deltaTime) override;
	void afterFixedUpdate(EntityList* entities, float deltaTime) override;
private:
	Window* win;

	SDL_Texture* getCachedTexture(std::string path);
	void removeUnusedTextures(EntityList* entities);
};

