#pragma once

#include "System.h"
#include "Entity.h"
#include <memory>
#include <functional>

#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include "CerealArchive.h"

struct Level
{
	EntityList entities;

	void clear()
	{
		for (auto& entity : entities)
		{
			entity.reset();
		}
	}

	template <class Archive>
	void serialize(Archive &ar)
	{
		ar(CEREAL_NVP(entities));
	}
};

class World
{
public:
	World();
	
	void tick(float deltaTime);
	void fixedTick(float deltaTime);

	void addEntity(Entity* entity);
	void eachEntity(std::function<void(std::shared_ptr<Entity>)> callback);
	
	void registerSystem(System* system);
	void eachSystem(std::function<void(std::shared_ptr<System>)> callback);

	void shutdown();

	void loadLevel(const std::string &filePath);
	void saveLevel(const std::string &filePath);

private:
	std::vector<std::shared_ptr<System>> systems;
	Level level;
};

