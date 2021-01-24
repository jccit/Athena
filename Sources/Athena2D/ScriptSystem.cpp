#include "ScriptSystem.h"

#include "Script.h"
#include "SqVM.h"

#include <Console/Console.h>

SqVM* vm;

ScriptSystem::ScriptSystem()
{
	vm = &SqVM::getInstance();
}

ScriptSystem::~ScriptSystem()
{
}

void ScriptSystem::init()
{
	LOG("Init", "ScriptSystem");
}

void ScriptSystem::shutdown()
{
	LOG("Shutdown", "ScriptSystem");
	vm->shutdown();
}

void ScriptSystem::preload(std::shared_ptr<Entity> entity, float deltaTime)
{
	std::shared_ptr<Script> script = entity->getComponent<Script>();

	if (script && !script->loaded && !script->failed)
	{
		try
		{
			LOG_VERBOSE("Compiling script " + script->src, "ScriptSystem");
			vm->runScript(script->src);
			LOG_VERBOSE(script->src + " compiled and loaded with no errors", "ScriptSystem");
		}
		catch (ssq::CompileException &e)
		{
			LOG_ERROR(e.what(), script->src);
			script->failed = true;
			return;
		}

		try {
			ssq::Class cls = vm->vm->findClass(script->className.c_str());
			ssq::Instance instance = vm->vm->newInstance(cls, entity.get());
			ssq::Function update = cls.findFunc("update");

			script->instance = new ssq::Instance(instance);
			script->update = new ssq::Function(update);

			script->loaded = true;
			script->failed = false;
		}
		catch (ssq::NotFoundException &e)
		{
			LOG_ERROR(e.what(), script->src);
			script->failed = true;
		}
		catch (ssq::TypeException& e)
		{
			LOG_ERROR(e.what(), script->src);
			script->failed = true;
		}
		catch (ssq::RuntimeException& e)
		{
			LOG_ERROR(e.what(), script->src);
			script->failed = true;
		}
	}
}

void ScriptSystem::beforeUpdate(float deltaTime)
{
}

void ScriptSystem::update(std::shared_ptr<Entity> entity, float deltaTime)
{
	std::shared_ptr<Script> script = entity->getComponent<Script>();

	if (script && script->loaded && !script->failed && script->update != nullptr)
	{
		try
		{
			vm->vm->callFunc(*script->update, *script->instance, deltaTime);
		}
		catch (ssq::RuntimeException &e)
		{
			LOG_ERROR(e.what(), script->src);
			script->failed = true;
		}
		catch (ssq::TypeException &e)
		{
			LOG_ERROR(e.what(), script->src);
			script->failed = true;
		}
	}
}

void ScriptSystem::afterUpdate(float deltaTime)
{
}
