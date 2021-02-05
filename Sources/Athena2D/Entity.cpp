#include "pch.h"
#include "Entity.h"


#include "Script.h"
#include "Sprite.h"

Entity::Entity()
{
	id = "";
	pos = Vec2();
	rot = 0.0f;
	auto* comps = new RawComponentList;
	components = std::shared_ptr<RawComponentList>(comps);
}

Entity::Entity(std::string newID)
{
	id = newID;
	pos = Vec2();
	rot = 0.0f;
	auto* comps = new RawComponentList;
	components = std::shared_ptr<RawComponentList>(comps);
}

Entity::~Entity()
{
	components.reset();
}

void Entity::removeComponent(ComponentType cid)
{
	components->erase(cid);
}

void Entity::translate(float x, float y)
{
	pos += Vec2(x, y);
}

void Entity::moveTo(float x, float y)
{
	pos = Vec2(x, y);
}

void Entity::addSprite(std::string src)
{
	Sprite* sprite = new Sprite();
	sprite->src = src;
	addComponent(sprite);
}

void Entity::addScript(std::string src, std::string className)
{
	Script* script = new Script();
	script->src = src;
	script->className = className;
	addComponent(script);
}