/**
 * @file Engine.cpp
 *
 * @brief The entry point for the game, containing init, game loop and shutdown code
 */

#include "Engine.h"

#include <chrono>
#include <SDL.h>
#include <SDL_image.h>

#include "SqVM.h"
#include "World.h"

#include "RenderSystem.h"
#include <Console/Console.h>
#include "FileOutput.h"
#include "Sprite.h"

SqVM* sq;
World world;

int Engine::init()
{
	Console::getInstance().registerOutput(new FileOutput());

	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	
	world.registerSystem(new RenderSystem());
	
	sq = new SqVM();

	sq->runScript("test.nut");


	// test

	Entity* ent = new Entity();
	Sprite* sprite = new Sprite();
	sprite->src = "test.png";
	ent->addComponent(sprite);
	ent->pos = Vec2(10.0f, 10.0f);
	world.addEntity(ent);
	
	return 0;
}

void Engine::shutdown()
{
	world.shutdown();

	delete sq;

	IMG_Quit();
	SDL_Quit();

	Console::getInstance().shutdown();
}

std::chrono::steady_clock::time_point previousTime;
bool firstRun = true;

void Engine::loop()
{
	bool running = true;
	SDL_Event e;

	while (running)
	{
		auto currentTime = std::chrono::steady_clock::now();
		if (firstRun) {
			previousTime = currentTime;
			firstRun = false;
		}
		
		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
			case SDL_QUIT:
				running = false;
			}
		}

		auto elapsed = currentTime - previousTime;
		double deltaTime = std::chrono::duration<double>(elapsed).count();
		previousTime = currentTime;

		world.tick(deltaTime);
	}
}
