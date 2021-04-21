#pragma once

#include "System.h"
#include "Script.h"
#include "SqVM.h"
#include <simplesquirrel/simplesquirrel.hpp>
#include <Console/Console.h>
#include <set>
#include <queue>

#include "KeyboardEvent.h"
#include "MouseMoveEvent.h"
#include "MouseButtonEvent.h"

class ScriptSystem : public System
{
public:
	ScriptSystem();
	virtual ~ScriptSystem();

	void init(World* world) override;
	void shutdown() override;
	void preload(std::shared_ptr<Entity> entity, float deltaTime) override;
	void beforeUpdate(EntityList* entities, float deltaTime) override;
	void update(EntityList* entities, float deltaTime) override;
	void afterUpdate(EntityList* entities, float deltaTime) override;

	void beforeFixedUpdate(EntityList* entities, float deltaTime) override;
	void fixedUpdate(std::shared_ptr<Entity> entity, float deltaTime) override;
	void afterFixedUpdate(EntityList* entities, float deltaTime) override;

	void keyEventHandler(KeyboardEvent* evt);
	void mouseMoveEventHandler(MouseMoveEvent* evt);
	void mouseButtonEventHandler(MouseButtonEvent* evt);

private:
	template<class... Args>
	void callFunc(std::shared_ptr<Script> script, ssq::Function* func, Args... args)
	{
		if (script && script->loaded && !script->failed && script->instance != nullptr && func != nullptr)
		{
			bool result = SqVM::getInstance().callFunc(script->src, script->instance, func, args...);
			if (!result) {
				script->failed = true;
			}
		}
	}

private:
	std::set<std::string> loadedScripts;
	std::queue<Event*> newEvents;
};

