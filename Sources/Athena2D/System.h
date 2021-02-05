#pragma once
#include "Component.h"
#include "Entity.h"

class World;

enum class SystemState
{
	INACTIVE = 0,
	ACTIVE = 1,
	FAILED = 2
};

class System
{
public:
	virtual ~System() = default;

	virtual void init(World* world) = 0;
	virtual void shutdown() = 0;

	virtual void preload(std::shared_ptr<Entity> entity, float deltaTime) = 0;
	virtual void beforeUpdate(EntityList *entities, float deltaTime) = 0;
	virtual void update(EntityList* entities, float deltaTime) = 0;
	virtual void afterUpdate(EntityList* entities, float deltaTime) = 0;

	virtual void beforeFixedUpdate(EntityList* entities, float deltaTime) = 0;
	virtual void fixedUpdate(std::shared_ptr<Entity> entity, float deltaTime) = 0;
	virtual void afterFixedUpdate(EntityList* entities, float deltaTime) = 0;

	SystemState state = SystemState::INACTIVE;
	bool ignorePause = false;

protected:
	ComponentSignature componentSignature;
};