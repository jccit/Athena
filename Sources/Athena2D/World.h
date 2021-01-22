#pragma once

#include "System.h"
#include "Entity.h"
#include <vector>
#include <memory>
#include <functional>

class World
{
public:
	World();
	
	void tick(double deltaTime);

	void addEntity(Entity* entity);
	void eachEntity(std::function<void(std::shared_ptr<Entity>)> callback);
	
	void registerSystem(System* system);
	void eachSystem(std::function<void(std::shared_ptr<System>)> callback);

	void shutdown();

private:
	std::vector<std::shared_ptr<System>> systems;
	std::vector<std::shared_ptr<Entity>> entities;
};

