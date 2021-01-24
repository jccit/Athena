#pragma once

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>

#include "Component.h"
#include <simplesquirrel/simplesquirrel.hpp>

struct Script final : public Component
{	
	std::string src;
	std::string className;

	ssq::Instance *instance;
	ssq::Function *update;

	bool loaded = false;
	bool failed = false;

	std::string toString() override
	{
		return src;
	}

	template <class Archive>
	void serialize(Archive& ar)
	{
		ar(src, className);
	}
};

CEREAL_REGISTER_TYPE(Script);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Script);