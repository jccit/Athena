#include "ScriptSystem.h"

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
		if (loadedScripts.find(script->src) == loadedScripts.end()) {
			try
			{
				LOG_VERBOSE("Compiling script " + script->src, "ScriptSystem");
				vm->runScript(script->src);
				LOG_VERBOSE(script->src + " compiled and loaded with no errors", "ScriptSystem");

				loadedScripts.insert(script->src);
			}
			catch (ssq::CompileException& e)
			{
				LOG_ERROR(e.what(), script->src);
				script->failed = true;
				return;
			}
		}

		ssq::Class cls;

		try {
			cls = vm->vm->findClass(script->className.c_str());
			ssq::Instance instance = vm->vm->newInstance(cls, entity.get());

			script->instance = new ssq::Instance(instance);

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

		if (script->failed)
			return;

		script->init = findFunc(cls, "init");
		script->update = findFunc(cls, "update");

		callFunc(script, script->init);
	}
}

void ScriptSystem::beforeUpdate(float deltaTime)
{
}

void ScriptSystem::update(std::shared_ptr<Entity> entity, float deltaTime)
{
	std::shared_ptr<Script> script = entity->getComponent<Script>();

	callFunc(script, script->update, deltaTime);
}

void ScriptSystem::afterUpdate(float deltaTime)
{
}

ssq::Function* ScriptSystem::findFunc(ssq::Class& cls, const std::string& name)
{
	try
	{
		ssq::Function func = cls.findFunc(name.c_str());
		return new ssq::Function(func);
	}
	catch (...)
	{
		// can't find func, return null
	}

	return nullptr;
}
