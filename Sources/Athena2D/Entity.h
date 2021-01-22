#pragma once

#include "ComponentManager.h"
#include "Component.h"
#include "Vec2.h"
#include <memory>

class Entity
{
public:
	Entity();
	~Entity();

	template <class C>
	inline void addComponent(C* c)
	{
		if (c == nullptr)
			return;

		const ComponentType cid = COMPONENT_TYPE(C);

		// Remove any existing components
		if (components[cid] != nullptr)
			removeComponent(cid);

		std::shared_ptr<Component> ptr(c);
		components[cid] = std::move(ptr);
	}

	void removeComponent(ComponentType cid);

	template <class C>
	inline std::shared_ptr<C> getComponent()
	{
		const ComponentType cid = COMPONENT_TYPE(C);
		return std::static_pointer_cast<C>(components[cid]);
	}

	template <class C>
	inline bool hasComponent()
	{
		const ComponentType cid = COMPONENT_TYPE(C);
		return components.count(cid);
	}
	
	Vec2 pos;
	Vec2 rot;

private:
	std::unordered_map<ComponentType, std::shared_ptr<Component>> components;
};


