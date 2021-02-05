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
#include "EventQueue.h"

#include "RenderSystem.h"
#include "ScriptSystem.h"
#include "Script.h"
#include "Sprite.h"
#include "SqVM.h"

#include <Console/Console.h>
#include "FileOutput.h"
#include "StdOutput.h"

#include <Utils/Filesystem.h>
#include <Console/CVar.h>

#include <imgui/backends/imgui_impl_sdl.h>
#include "ImGuiHelper.h"

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
	Console::getInstance().registerOutput(std::shared_ptr<IOutput>(new FileOutput()));
	Console::getInstance().registerOutput(std::shared_ptr<IOutput>(new StdOutput()));

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
	// world.registerSystem(new PhysicsSystem());

	SqVM::getInstance().runScript("core/EntityScript.nut");

	SqVM::getInstance().exec("::world <- World();\nfunction _bindWorld(w){\nworld=w;\n}");
	ssq::Function bindWorld = SqVM::getInstance().vm->findFunc("_bindWorld");
	SqVM::getInstance().vm->callFunc(bindWorld, *SqVM::getInstance().vm, &world);

	// test
	
	Entity* ent = new Entity();
	Sprite* sprite = new Sprite();
	Script* script = new Script();
	sprite->src = "test.png";
	script->src = "player.nut";
	script->className = "Player";
	ent->addComponent(sprite);
	ent->addComponent(script);
	ent->pos = Vec2(10.0f, 400.0f);
	ent->id = "player";
	world.addEntity(ent);

	Entity* ent2 = new Entity();
	Sprite* sprite2 = new Sprite();
	sprite2->src = "test.png";
	sprite2->layer = SpriteLayer::BACKGROUND;
	ent2->pos = Vec2(50.0f, 10.0f);
	ent2->rot = 60.0f;
	ent2->id = "enemy";
	ent2->addComponent(sprite2);
	world.addEntity(ent2);
	
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
			ImGui_ImplSDL2_ProcessEvent(&e);
			
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
					if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
						world.togglePause();
					
					if (!ImGuiHelper::wantsKeyboard()) {
						std::string keyName = std::string(SDL_GetKeyName(e.key.keysym.sym));
						EventQueue::getInstance().publish(new KeyboardEvent(keyName, down));
					}
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
