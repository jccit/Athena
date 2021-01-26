#pragma once

#include "System.h"
#include "Window.h"

class RenderSystem final : public System
{
public:
	RenderSystem();
	virtual ~RenderSystem();

	void init() override;
	void shutdown() override;

	void preload(std::shared_ptr<Entity> entity, float deltaTime) override;
	void beforeUpdate(EntityList* entities, float deltaTime) override;
	void update(std::shared_ptr<Entity> entity, float deltaTime) override;
	void afterUpdate(EntityList* entities, float deltaTime) override;

private:
	Window* win;
};

