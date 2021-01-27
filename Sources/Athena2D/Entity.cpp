#include "pch.h"
#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

void Entity::removeComponent(ComponentType cid)
{
	components.erase(cid);
}

void Entity::translate(float x, float y)
{
	pos += Vec2(x, y);
}

void Entity::moveTo(float x, float y)
{
	pos = Vec2(x, y);
}
