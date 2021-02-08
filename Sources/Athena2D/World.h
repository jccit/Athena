#pragma once

#include "System.h"
#include "Entity.h"
#include <memory>
#include <functional>

#include <simplesquirrel/simplesquirrel.hpp>

#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include "CerealArchive.h"

struct Level
{
	EntityList entities;

	void clear()
	{
		entities.clear();
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

	static void expose(ssq::VM& vm);
	
	void tick(float deltaTime);
	void fixedTick(float deltaTime);

	void addEntity(Entity* entity);
	void eachEntity(std::function<void(std::shared_ptr<Entity>)> callback);
	std::shared_ptr<Entity> getEntity(std::string id);
	Entity* newEntity(std::string id);
	void removeEntity(std::string id);
	
	void registerSystem(System* system);
	void eachSystem(std::function<void(std::shared_ptr<System>)> callback);

	void shutdown();

	void loadLevel(const std::string &filePath);
	void saveLevel(const std::string &filePath);

	bool isPaused();
	void setPaused(bool p);
	void togglePause();

private:
	std::vector<std::shared_ptr<System>> systems;
	std::string getNewID();
	uint64_t lastID = 0;
	Level level;
	bool paused = false;
};

