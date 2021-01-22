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

	void preload(std::shared_ptr<Entity> entity, double deltaTime) override;
	void beforeUpdate(double deltaTime) override;
	void update(std::shared_ptr<Entity> entity, double deltaTime) override;
	void afterUpdate(double deltaTime) override;

private:
	Window* win;
};

