#pragma once

#include "System.h"

class ScriptSystem : public System
{
public:
	ScriptSystem();
	virtual ~ScriptSystem();

	void init() override;
	void shutdown() override;
	void preload(std::shared_ptr<Entity> entity, float deltaTime) override;
	void beforeUpdate(float deltaTime) override;
	void update(std::shared_ptr<Entity> entity, float deltaTime) override;
	void afterUpdate(float deltaTime) override;
};

