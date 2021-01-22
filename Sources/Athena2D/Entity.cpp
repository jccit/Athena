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
