#include "pch.h"
#include "World.h"
#include "ComponentManager.h"
#include "Script.h"
#include "Sprite.h"
#include "Rigidbody.h"

#include <Utils/Filesystem.h>
#include <Console/Console.h>

World::World()
{
	REGISTER_COMPONENT(Sprite);
	REGISTER_COMPONENT(Script);
	REGISTER_COMPONENT(Rigidbody);
}

void World::tick(float deltaTime)
{
	
	eachSystem([this, deltaTime](std::shared_ptr<System> system)
	{
		eachEntity([system, deltaTime](std::shared_ptr<Entity> entity)
		{
			system->preload(entity, deltaTime);
		});
	});

	eachSystem([this, deltaTime](std::shared_ptr<System> system)
	{
		system->beforeUpdate(&level.entities, deltaTime);
	});
	
	eachSystem([this, deltaTime](std::shared_ptr<System> system)
	{
		eachEntity([system, deltaTime](std::shared_ptr<Entity> entity)
		{
			system->update(entity, deltaTime);
		});
	});

	eachSystem([this, deltaTime](std::shared_ptr<System> system)
	{
		system->afterUpdate(&level.entities, deltaTime);
	});
}

void World::fixedTick(float deltaTime)
{
	eachSystem([this, deltaTime](std::shared_ptr<System> system)
	{
		system->beforeFixedUpdate(&level.entities, deltaTime);
	});

	eachSystem([this, deltaTime](std::shared_ptr<System> system)
	{
		eachEntity([system, deltaTime](std::shared_ptr<Entity> entity)
		{
			system->fixedUpdate(entity, deltaTime);
		});
	});

	eachSystem([this, deltaTime](std::shared_ptr<System> system)
	{
		system->afterFixedUpdate(&level.entities, deltaTime);
	});
}

void World::addEntity(Entity* entity)
{
	std::shared_ptr<Entity> ptr(entity);
	level.entities.push_back(std::move(ptr));
}

void World::eachEntity(std::function<void(std::shared_ptr<Entity>)> callback)
{
	for (auto& entity : level.entities)
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
		system->shutdown();
		system.reset();
	}

	level.clear();
}

void World::loadLevel(const std::string &filePath)
{
	std::ifstream file = FS_OpenFileRead(filePath);
	CEREAL_INPUT archive(file);

	level.clear();

	archive(level);

	LOG("Loaded level " + filePath, "World");
}

void World::saveLevel(const std::string &filePath)
{
	std::ofstream file = FS_OpenFileWrite(filePath);
	CEREAL_OUTPUT archive(file);

	archive(CEREAL_NVP(level));

	LOG("Saved level " + filePath, "World");
}
