#pragma once

#include "System.h"
#include "Script.h"
#include "SqVM.h"
#include <simplesquirrel/simplesquirrel.hpp>
#include <Console/Console.h>
#include <set>
#include <queue>

#include "KeyboardEvent.h"

class ScriptSystem : public System
{
public:
	ScriptSystem();
	virtual ~ScriptSystem();

	void init(World* world) override;
	void shutdown() override;
	void preload(std::shared_ptr<Entity> entity, float deltaTime) override;
	void beforeUpdate(EntityList* entities, float deltaTime) override;
	void update(std::shared_ptr<Entity> entity, float deltaTime) override;
	void afterUpdate(EntityList* entities, float deltaTime) override;

	void beforeFixedUpdate(EntityList* entities, float deltaTime) override;
	void fixedUpdate(std::shared_ptr<Entity> entity, float deltaTime) override;
	void afterFixedUpdate(EntityList* entities, float deltaTime) override;

	void keyEventHandler(KeyboardEvent* evt);

private:
	static ssq::Function* findFunc(ssq::Class& cls, const std::string &name);

	template<class... Args>
	void callFunc(std::shared_ptr<Script> script, ssq::Function* func, Args... args)
	{
		if (script && script->loaded && !script->failed && script->instance != nullptr && func != nullptr)
		{
			try
			{
				SqVM::getInstance().vm->callFunc(*func, *script->instance, args...);
			}
			catch (ssq::RuntimeException& e)
			{
				LOG_ERROR(e.what(), script->src);
				script->failed = true;
			}
			catch (ssq::TypeException& e)
			{
				LOG_ERROR(e.what(), script->src);
				script->failed = true;
			}
		}
	}

private:
	std::set<std::string> loadedScripts;
	std::queue<Event*> newEvents;
};

