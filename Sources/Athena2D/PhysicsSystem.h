#pragma once

#include "System.h"

class PhysicsSystem : public System
{
public:
	PhysicsSystem();

	void init(World* world) override;
	void shutdown() override;
	void preload(std::shared_ptr<Entity> entity, float deltaTime) override;
	void beforeUpdate(EntityList* entities, float deltaTime) override;
	void update(std::shared_ptr<Entity> entity, float deltaTime) override;
	void afterUpdate(EntityList* entities, float deltaTime) override;
	void beforeFixedUpdate(EntityList* entities, float deltaTime) override;
	void fixedUpdate(std::shared_ptr<Entity> entity, float deltaTime) override;
	void afterFixedUpdate(EntityList* entities, float deltaTime) override;
};

