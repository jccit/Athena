#include "pch.h"
#include "ScriptSystem.h"

SqVM* vm;

ScriptSystem::ScriptSystem()
{
	vm = &SqVM::getInstance();
}

ScriptSystem::~ScriptSystem()
{
}

void ScriptSystem::init(World* world)
{
	LOG("Init", "ScriptSystem");

	EventQueue::getInstance().subscribe(this, &ScriptSystem::keyEventHandler);
	EventQueue::getInstance().subscribe(this, &ScriptSystem::mouseMoveEventHandler);
	EventQueue::getInstance().subscribe(this, &ScriptSystem::mouseButtonEventHandler);
}

void ScriptSystem::shutdown()
{
	LOG("Shutdown", "ScriptSystem");
	vm->shutdown();
}

void ScriptSystem::preload(std::shared_ptr<Entity> entity, float deltaTime)
{
	if (entity) {
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
			catch (ssq::NotFoundException& e)
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
			script->keyDown = findFunc(cls, "keyDown");
			script->keyUp = findFunc(cls, "keyUp");
			script->mouseMove = findFunc(cls, "mouseMove");
			script->mouseDown = findFunc(cls, "mouseDown");
			script->mouseUp = findFunc(cls, "mouseUp");

			callFunc(script, script->init);
		}
	}
}

void ScriptSystem::beforeUpdate(EntityList* entities, float deltaTime)
{
	while (!newEvents.empty())
	{
		Event* evt = newEvents.front();
		newEvents.pop();

		if (KeyboardEvent* keyEvt = dynamic_cast<KeyboardEvent*>(evt))
		{
			for (auto [id, entity] : *entities)
			{
				if (entity) {
					std::shared_ptr<Script> s = entity->getComponent<Script>();
					if (s && s->loaded && !s->failed)
					{
						ssq::Function* evtFunc = keyEvt->isDown ? s->keyDown : s->keyUp;

						if (evtFunc != nullptr)
							callFunc(s, evtFunc, keyEvt->keyName);
					}
				}
			}
		}
		else if (MouseMoveEvent* moveEvt = dynamic_cast<MouseMoveEvent*>(evt))
		{
			for (auto [id, entity] : *entities)
			{
				if (entity) {
					std::shared_ptr<Script> s = entity->getComponent<Script>();
					if (s && s->loaded && !s->failed)
					{
						ssq::Function* evtFunc = s->mouseMove;

						if (evtFunc != nullptr)
							callFunc(s, evtFunc, moveEvt->x, moveEvt->y);
					}
				}
			}
		}
		else if (MouseButtonEvent* btnEvt = dynamic_cast<MouseButtonEvent*>(evt))
		{
			for (auto [id, entity] : *entities)
			{
				if (entity) {
					std::shared_ptr<Script> s = entity->getComponent<Script>();
					if (s && s->loaded && !s->failed)
					{
						ssq::Function* evtFunc = btnEvt->down ? s->mouseDown : s->mouseUp;

						if (evtFunc != nullptr)
							callFunc(s, evtFunc, btnEvt->button);
					}
				}
			}
		}
	}
}

void ScriptSystem::update(EntityList* entities, float deltaTime)
{
	for (auto [id, entity] : *entities)
	{
		if (entity) {
			std::shared_ptr<Script> script = entity->getComponent<Script>();

			if (script && script->loaded && !script->failed)
				callFunc(script, script->update, deltaTime);
		}
	}
}

void ScriptSystem::afterUpdate(EntityList* entities, float deltaTime)
{
}

void ScriptSystem::beforeFixedUpdate(EntityList* entities, float deltaTime)
{
}

void ScriptSystem::fixedUpdate(std::shared_ptr<Entity> entity, float deltaTime)
{
}

void ScriptSystem::afterFixedUpdate(EntityList* entities, float deltaTime)
{
}

void ScriptSystem::keyEventHandler(KeyboardEvent* evt)
{
	newEvents.push(evt);
}

void ScriptSystem::mouseMoveEventHandler(MouseMoveEvent* evt)
{
	newEvents.push(evt);
}

void ScriptSystem::mouseButtonEventHandler(MouseButtonEvent* evt)
{
	newEvents.push(evt);
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
