/**
 * @file Engine.cpp
 *
 * @brief The entry point for the game, containing init, game loop and shutdown code
 */

#include "Engine.h"

#include <chrono>
#include <SDL.h>
#include <SDL_image.h>

#include "ScriptSystem.h"
#include "World.h"

#include "RenderSystem.h"
#include <Console/Console.h>
#include "FileOutput.h"
#include "StdOutput.h"
#include "Script.h"
#include "Sprite.h"
#include "SqVM.h"

#include "EventQueue.h"

World world;

struct TestStruct
{
	std::string id;
	uint32_t verts;
	std::string sprite;

	template <class Archive>
	void serialize(Archive &ar)
	{
		ar(id, verts, sprite);
	}
};

int Engine::init()
{
	Console::getInstance().registerOutput(new FileOutput());
	Console::getInstance().registerOutput(new StdOutput());

	LOG("Init", "Engine");

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	
	world.registerSystem(new RenderSystem());
	world.registerSystem(new ScriptSystem());

	SqVM::getInstance().runScript("core/EntityScript.nut");

	// test

	/*
	Entity* ent = new Entity();
	Sprite* sprite = new Sprite();
	Script* script = new Script();
	sprite->src = "test.png";
	script->src = "test.nut";
	script->className = "TestEnt";
	ent->addComponent(sprite);
	ent->addComponent(script);
	ent->pos = Vec2(10.0f, 10.0f);
	ent->id = "testEnt";
	world.addEntity(ent);
	world.saveLevel("test.lvl");
	*/

	world.loadLevel("test.lvl");
	
	return 0;
}

void Engine::shutdown()
{
	world.shutdown();

	IMG_Quit();
	SDL_Quit();

	LOG("So long and thanks for all the fish", "Engine");

	Console::getInstance().shutdown();
}

std::chrono::steady_clock::time_point previousTime;
bool firstRun = true;

void Engine::loop()
{
	bool running = true;
	SDL_Event e;

	LOG_VERBOSE("Starting game loop", "Engine");

	while (running)
	{
		auto currentTime = std::chrono::steady_clock::now();
		if (firstRun) {
			previousTime = currentTime;
			firstRun = false;
		}
		
		while (SDL_PollEvent(&e))
		{
			bool down = true;
			
			switch (e.type)
			{
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYUP:
				down = false;
			case SDL_KEYDOWN:
				if (e.key.repeat == 0) {
					std::string keyName = std::string(SDL_GetKeyName(e.key.keysym.sym));
					EventQueue::getInstance().publish(new KeyboardEvent(keyName, down));
				}
				break;
			}
		}

		auto elapsed = currentTime - previousTime;
		float deltaTime = std::chrono::duration<float>(elapsed).count();
		previousTime = currentTime;

		world.tick(deltaTime);
	}
}
