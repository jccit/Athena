#pragma once
#include <bitset>
#include <string>

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using ComponentSignature = std::bitset<MAX_COMPONENTS>;

struct Component
{
	virtual ~Component() = default;
	virtual std::string toString() = 0;
};