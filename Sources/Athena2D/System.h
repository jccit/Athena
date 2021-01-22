#pragma once
#include "Component.h"
#include "Entity.h"

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

	virtual void init() = 0;
	virtual void shutdown() = 0;

	virtual void preload(std::shared_ptr<Entity> entity, double deltaTime) = 0;
	virtual void beforeUpdate(double deltaTime) = 0;
	virtual void update(std::shared_ptr<Entity> entity, double deltaTime) = 0;
	virtual void afterUpdate(double deltaTime) = 0;

	SystemState state = SystemState::INACTIVE;

protected:
	ComponentSignature componentSignature;
};