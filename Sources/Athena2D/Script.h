#pragma once

#include "Component.h"
#include <simplesquirrel/simplesquirrel.hpp>

struct Script : Component
{	
	std::string src;
	std::string className;

	ssq::Instance *instance;
	ssq::Function *update;

	bool loaded = false;
	bool failed = false;
};