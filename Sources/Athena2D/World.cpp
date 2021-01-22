#include "World.h"
#include "ComponentManager.h"
#include "Sprite.h"

World::World()
{
	REGISTER_COMPONENT(Sprite);
}

void World::tick(double deltaTime)
{
	eachSystem([this, deltaTime](std::shared_ptr<System> system)
	{
		eachEntity([system, deltaTime](std::shared_ptr<Entity> entity)
		{
			system->preload(entity, deltaTime);
		});
	});

	eachSystem([deltaTime](std::shared_ptr<System> system)
	{
		system->beforeUpdate(deltaTime);
	});
	
	eachSystem([this, deltaTime](std::shared_ptr<System> system)
	{
		eachEntity([system, deltaTime](std::shared_ptr<Entity> entity)
		{
			system->update(entity, deltaTime);
		});
	});

	eachSystem([deltaTime](std::shared_ptr<System> system)
	{
		system->afterUpdate(deltaTime);
	});
}

void World::addEntity(Entity* entity)
{
	std::shared_ptr<Entity> ptr(entity);
	entities.push_back(std::move(ptr));
}

void World::eachEntity(std::function<void(std::shared_ptr<Entity>)> callback)
{
	for (auto& entity : entities)
	{
		callback(entity);
	}
}

void World::registerSystem(System* system)
{
	std::shared_ptr<System> ptr(system);
	ptr->init();
	systems.push_back(std::move(ptr));
}

void World::eachSystem(std::function<void(std::shared_ptr<System>)> callback)
{
	for (auto& system : systems)
	{
		callback(system);
	}
}

void World::shutdown()
{
	for (auto& system : systems)
	{
		system.reset();
	}
}
