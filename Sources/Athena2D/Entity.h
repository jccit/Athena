#pragma once

#include "ComponentManager.h"
#include "Component.h"
#include "Vec2.h"
#include <memory>
#include <simplesquirrel/vm.hpp>

#include <cereal/types/memory.hpp>
#include <cereal/types/unordered_map.hpp>
#include <cereal/access.hpp>

typedef std::unordered_map<ComponentType, std::shared_ptr<Component>> RawComponentList;
typedef std::shared_ptr<RawComponentList> ComponentList;

class Entity
{
public:
	Entity();
	Entity(std::string newID);
	~Entity();

	template <class C>
	inline void addComponent(C* c)
	{
		if (c == nullptr)
			return;

		const ComponentType cid = COMPONENT_TYPE(C);

		// Remove any existing components
		if (components->count(cid) && components->at(cid) != nullptr)
			removeComponent(cid);

		std::shared_ptr<Component> ptr(c);
		components->insert({ cid, std::move(ptr) });
	}

	void removeComponent(ComponentType cid);

	template <class C>
	inline std::shared_ptr<C> getComponent()
	{
		const ComponentType cid = COMPONENT_TYPE(C);

		if (!components->count(cid))
			return std::shared_ptr<C>(nullptr);
		
		return std::static_pointer_cast<C>(components->at(cid));
	}

	template <class C>
	inline bool hasComponent()
	{
		const ComponentType cid = COMPONENT_TYPE(C);
		return components->count(cid);
	}

	void translate(float x, float y);
	void moveTo(float x, float y);

	void addSprite(std::string src);
	void addScript(std::string src, std::string className);

	static void expose(ssq::VM& vm)
	{
		ssq::Class cls = vm.addClass("Entity", ssq::Class::Ctor < Entity() > ());
		cls.addVar("pos", &Entity::pos);
		cls.addVar("rot", &Entity::rot);
		cls.addVar("origin", &Entity::origin);
		cls.addVar("id", &Entity::id);

		cls.addFunc("translate", &Entity::translate);
		cls.addFunc("moveTo", &Entity::moveTo);

		cls.addFunc("addSprite", &Entity::addSprite);
		cls.addFunc("addScript", &Entity::addScript);
	}

	std::string id;
	Vec2 pos;
	float rot;
	Vec2 origin;

private:
	ComponentList components;

	friend class cereal::access;

	template <class Archive>
	void serialize(Archive &ar)
	{
		ar(
			CEREAL_NVP(id),
			CEREAL_NVP(pos),
			CEREAL_NVP(rot),
			CEREAL_NVP(components)
		);
	}
};

typedef std::map<std::string, std::shared_ptr<Entity>> EntityList;