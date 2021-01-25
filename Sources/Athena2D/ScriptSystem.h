#pragma once

#include "System.h"
#include "Script.h"
#include "SqVM.h"
#include <simplesquirrel/simplesquirrel.hpp>
#include <Console/Console.h>
#include <set>

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

	std::set<std::string> loadedScripts;
};

