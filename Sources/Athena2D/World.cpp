#include "pch.h"

#include "ComponentManager.h"
#include "Script.h"
#include "Sprite.h"
#include "World.h"

#ifdef PHYSICS
#include "Rigidbody.h"
#endif

#include <Filesystem/Raw.h>

World::World()
{
    REGISTER_COMPONENT(Sprite);
    REGISTER_COMPONENT(Script);

#ifdef PHYSICS
    REGISTER_COMPONENT(Rigidbody);
#endif
}

void World::init()
{
    camera = new Camera();
    camera->loadScript();
}

void World::expose(ssq::VM& vm)
{
    ssq::Class cls = vm.addClass("World", ssq::Class::Ctor<World()>());

    cls.addFunc("newEntity", &World::newEntity);
    cls.addFunc("getEntity", &World::getEntity);
    cls.addFunc("removeEntity", &World::removeEntity);
}

void World::tick(float deltaTime)
{
    eachSystem([this, deltaTime](std::shared_ptr<System> system) {
        eachEntity([system, deltaTime](std::shared_ptr<Entity> entity) {
            system->preload(entity, deltaTime);
        });
    });

    eachSystem([this, deltaTime](std::shared_ptr<System> system) {
        system->beforeUpdate(&level.entities, deltaTime);
    });

    eachSystem([this, deltaTime](std::shared_ptr<System> system) {
        system->update(&level.entities, deltaTime);
    });

    eachSystem([this, deltaTime](std::shared_ptr<System> system) {
        system->afterUpdate(&level.entities, deltaTime);
    });

    // Process our remove queue outside of any iterators
    while (!removeQueue.empty()) {
        std::string idToRemove = removeQueue.front();

        level.entities.erase(idToRemove);

        removeQueue.pop();
    }
}

void World::fixedTick(float deltaTime)
{
    eachSystem([this, deltaTime](std::shared_ptr<System> system) {
        system->beforeFixedUpdate(&level.entities, deltaTime);
    });

    eachSystem([this, deltaTime](std::shared_ptr<System> system) {
        eachEntity([system, deltaTime](std::shared_ptr<Entity> entity) {
            system->fixedUpdate(entity, deltaTime);
        });
    });

    eachSystem([this, deltaTime](std::shared_ptr<System> system) {
        system->afterFixedUpdate(&level.entities, deltaTime);
    });
}

void World::addEntity(Entity* entity)
{
    std::shared_ptr<Entity> ptr(entity);
    if (ptr->id.empty())
        ptr->id = getNewID();

    level.entities[ptr->id] = std::move(ptr);
}

void World::eachEntity(std::function<void(std::shared_ptr<Entity>)> callback)
{
    for (auto& entity : level.entities) {
        callback(entity.second);
    }
}

Entity* World::getEntity(std::string id)
{
    if (level.entities.count(id) > 0) {
        return level.entities[id].get();
    }

    return nullptr;
}

Entity* World::newEntity(std::string id)
{
    std::string newId = id;
    if (level.entities.count(id) > 0) {
        newId += std::to_string(getNewIDNum());
    }

    Entity* ent = new Entity(newId);
    std::shared_ptr<Entity> sharedEnt = std::shared_ptr<Entity>(ent);
    level.entities[ent->id] = sharedEnt;
    return ent;
}

void World::removeEntity(std::string id)
{
    // Process the removal after each tick
    removeQueue.push(id);
}

void World::registerSystem(System* system)
{
    std::shared_ptr<System> ptr(system);
    ptr->init(this);
    systems.push_back(std::move(ptr));
}

void World::eachSystem(std::function<void(std::shared_ptr<System>)> callback)
{
    for (auto& system : systems) {
        if (!paused || system->ignorePause)
            callback(system);
    }
}

void World::shutdown()
{
    delete camera;

    for (auto& system : systems) {
        system->shutdown();
        system.reset();
    }

    level.clear();
}

void World::loadLevel(const std::string& filePath)
{
    std::ifstream file = FS_OpenFileRead(filePath);
    CEREAL_INPUT archive(file);

    level.clear();

    archive(level);

    LOG("Loaded level " + filePath, "World");
}

void World::saveLevel(const std::string& filePath)
{
    std::ofstream file = FS_OpenFileWrite(filePath);
    CEREAL_OUTPUT archive(file);

    archive(CEREAL_NVP(level));

    LOG("Saved level " + filePath, "World");
}

bool World::isPaused()
{
    return paused;
}

void World::setPaused(bool p)
{
    paused = p;
}

void World::togglePause()
{
    setPaused(!paused);
}

std::string World::getNewID()
{
    return "entity" + std::to_string(getNewIDNum());
}

uint64_t World::getNewIDNum()
{
    lastID++;
    return lastID;
}
