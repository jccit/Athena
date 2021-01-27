/**
 * @file Engine.cpp
 *
 * @brief The entry point for the game, containing init, game loop and shutdown code
 */

#include "pch.h"
#include "Engine.h"

#include <chrono>
#include <SDL.h>
#include <SDL_image.h>

#include "World.h"

#include "RenderSystem.h"
#include "ScriptSystem.h"
#include "PhysicsSystem.h"
#include <Console/Console.h>
#include "FileOutput.h"
#include "StdOutput.h"
#include "Script.h"
#include "Sprite.h"
#include "SqVM.h"

#include "EventQueue.h"

#include <Utils/Filesystem.h>
#include <Console/CVar.h>

#include "Rigidbody.h"

World world;
CVar timestep = CVar("phys_timestep", 60, CVAR_PERSIST);

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

	std::string cfg = FS_ReadString(FS_UserDir() + "\\Athena\\config.cfg");
	std::stringstream ss(cfg);
	std::string cmd;

	while (std::getline(ss, cmd, '\n'))
	{
		Console::getInstance().exec(cmd);
	}

	LOG("Init", "Engine");

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	
	world.registerSystem(new RenderSystem());
	world.registerSystem(new ScriptSystem());
	world.registerSystem(new PhysicsSystem());

	SqVM::getInstance().runScript("core/EntityScript.nut");

	// test
	
	Entity* ent = new Entity();
	Sprite* sprite = new Sprite();
	Script* script = new Script();
	Rigidbody* playerrb = new Rigidbody();
	playerrb->type = b2_staticBody;
	sprite->src = "test.png";
	script->src = "test.nut";
	script->className = "TestEnt";
	ent->addComponent(sprite);
	ent->addComponent(script);
	ent->addComponent(playerrb);
	ent->pos = Vec2(10.0f, 400.0f);
	ent->id = "testEnt";
	world.addEntity(ent);

	Entity* ent2 = new Entity();
	Sprite* sprite2 = new Sprite();
	Rigidbody* rb = new Rigidbody();
	sprite2->src = "test.png";
	ent2->pos = Vec2(50.0f, 10.0f);
	ent2->rot = 60.0f;
	ent2->addComponent(sprite2);
	ent2->addComponent(rb);
	world.addEntity(ent2);

	Entity* floor = new Entity();
	Rigidbody* staticrb = new Rigidbody();
	staticrb->type = b2_kinematicBody;
	staticrb->width = 3000;
	staticrb->height = 20;
	floor->addComponent(staticrb);
	floor->pos = Vec2(0.0f, 520.0f);
	world.addEntity(floor);
	
	world.saveLevel("test.lvl");

	//world.loadLevel("test.lvl");

	
	return 0;
}

void Engine::shutdown()
{
	// Save cfg
	std::string cfg = Console::getInstance().getCfgFile();
	FS_WriteString(FS_UserDir() + "\\Athena\\config.cfg", cfg);
	
	world.shutdown();

	IMG_Quit();
	SDL_Quit();

	LOG("So long and thanks for all the fish", "Engine");

	Console::getInstance().shutdown();
}

std::chrono::steady_clock::time_point previousTime;
float accumulator = 0.0f;
float fixedTimestep = 1.0f / static_cast<float>(timestep.getInt());
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

				if (e.key.keysym.sym == SDLK_ESCAPE)
				{
					running = false;
				}
				break;
			}
		}

		auto elapsed = currentTime - previousTime;
		float deltaTime = std::chrono::duration<float>(elapsed).count();
		previousTime = currentTime;
		accumulator += deltaTime;
		fixedTimestep = 1.0f / static_cast<float>(timestep.getInt());

		while (accumulator >= fixedTimestep)
		{
			world.fixedTick(fixedTimestep);
			accumulator -= fixedTimestep;
		}

		world.tick(deltaTime);
	}
}
