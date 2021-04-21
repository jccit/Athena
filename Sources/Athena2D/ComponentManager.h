#pragma once

#include "Component.h"
#include <unordered_map>

#ifdef _WIN32
#include <vcruntime_typeinfo.h>
#endif

#define REGISTER_COMPONENT(comp) ComponentManager::getInstance().registerComponent<comp>()
#define COMPONENT_TYPE(comp) ComponentManager::getInstance().getComponentType<comp>()

class ComponentManager
{
public:
	ComponentManager(ComponentManager const&) = delete;
	void operator=(ComponentManager const&) = delete;
	
	template <typename C>
	void registerComponent()
	{
		const char* typeName = typeid(C).name();
		componentTypes.insert({ typeName, nextComponentType });
		nextComponentType++;
	}

	template <typename C>
	ComponentType getComponentType()
	{
		const char* typeName = typeid(C).name();
		return componentTypes[typeName];
	}

	static ComponentManager& getInstance()
	{
		static ComponentManager instance;
		return instance;
	}

private:
	std::unordered_map<const char*, ComponentType> componentTypes;
	ComponentType nextComponentType = 0;

	ComponentManager() {}
};

