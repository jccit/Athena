#include "pch.h"
#include "PhysicsSystem.h"
#include <box2d/b2_world.h>
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <Console/CVar.h>
#include <Console/Console.h>

#include "Rigidbody.h"
#include "Sprite.h"

#define PHYS_SCALE 15.0f

b2Vec2 gravity(0.0f, 50.0f);
b2World world(gravity);

CVar velocityIters = CVar("phys_iter_vel", 8, CVAR_PERSIST);
CVar positionIters = CVar("phys_iter_pos", 3, CVAR_PERSIST);

PhysicsSystem::PhysicsSystem()
{
}

void PhysicsSystem::init(World* world)
{
	LOG("Init", "PhysicsSystem");
}

void PhysicsSystem::shutdown()
{
	LOG("Shutdown", "PhysicsSystem");
}

void PhysicsSystem::preload(std::shared_ptr<Entity> entity, float deltaTime)
{
	std::shared_ptr<Rigidbody> rigidbody = entity->getComponent<Rigidbody>();

	if (rigidbody && rigidbody->body == nullptr) {
		int width = rigidbody->width;
		int height = rigidbody->height;

		if (width == 0 && height == 0)
		{
			std::shared_ptr<Sprite> sprite = entity->getComponent<Sprite>();

			if (sprite && sprite->loaded) {
				width = sprite->width;
				height = sprite->width;
			}
		}

		if (width == 0 && height == 0)
		{
			return;
		}
		
		b2BodyDef def;
		def.type = rigidbody->type;
		def.position.Set(entity->pos.x / PHYS_SCALE, entity->pos.y / PHYS_SCALE);
		def.angle = entity->rot * (b2_pi / 180.0f);
		rigidbody->body = world.CreateBody(&def);
		
		b2PolygonShape box;
		box.SetAsBox((static_cast<float>(width) / PHYS_SCALE) / 2.0f, (static_cast<float>(height) / PHYS_SCALE) / 2.0f);

		if (def.type == b2_dynamicBody)
		{
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &box;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.3f;
			rigidbody->body->CreateFixture(&fixtureDef);
		}
		else
		{
			rigidbody->lastPos = entity->pos;
			rigidbody->body->CreateFixture(&box, 0.0f);
		}
	}
}

void PhysicsSystem::beforeUpdate(EntityList* entities, float deltaTime)
{
}

void PhysicsSystem::update(EntityList* entities, float deltaTime)
{
}

void PhysicsSystem::afterUpdate(EntityList* entities, float deltaTime)
{
}

void PhysicsSystem::beforeFixedUpdate(EntityList* entities, float deltaTime)
{
	world.Step(deltaTime, velocityIters.getInt(), positionIters.getInt());
}

void PhysicsSystem::fixedUpdate(std::shared_ptr<Entity> entity, float deltaTime)
{
	std::shared_ptr<Rigidbody> rigidbody = entity->getComponent<Rigidbody>();

	if (rigidbody && rigidbody->body != nullptr) {
		if (rigidbody->type == b2_dynamicBody)
		{
			b2Vec2 pos = rigidbody->body->GetPosition();
			entity->pos.x = pos.x * PHYS_SCALE;
			entity->pos.y = pos.y * PHYS_SCALE;
			entity->rot = rigidbody->body->GetAngle() * (180.0f / b2_pi);
			rigidbody->body->SetAwake(true); // TODO: Remove this! Figure out why tf kinematic objects won't wake dynamic ones
		}
		else
		{
			// TODO: Calculate velocity based on last pos, move using velocity instead
			b2Vec2 vel;
			vel.x = ((entity->pos.x - rigidbody->lastPos.x) / deltaTime / PHYS_SCALE);
			vel.y = ((entity->pos.y - rigidbody->lastPos.y) / deltaTime / PHYS_SCALE);
			
			b2Vec2 pos;
			pos.x = entity->pos.x / PHYS_SCALE;
			pos.y = entity->pos.y / PHYS_SCALE;
			rigidbody->body->SetLinearVelocity(vel);
			rigidbody->body->SetTransform(pos, entity->rot * (b2_pi / 180.0f));

			rigidbody->lastPos = entity->pos;
		}
	}
}

void PhysicsSystem::afterFixedUpdate(EntityList* entities, float deltaTime)
{
}
