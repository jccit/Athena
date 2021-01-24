#pragma once

#include <cereal/types/polymorphic.hpp>
#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>

#include "Component.h"
#include <SDL.h>

struct Sprite final : public Component
{
	std::string src;
	SDL_Texture* texture;

	int width = 0;
	int height = 0;
	
	bool loaded = false;
	bool failed = false;

	~Sprite()
	{
		if (texture != nullptr)
		{
			SDL_DestroyTexture(texture);
		}
	}

	std::string toString() override
	{
		return src;
	}

	template <class Archive>
	void serialize(Archive &ar)
	{
		ar(src);
	}
};

CEREAL_REGISTER_TYPE(Sprite);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Sprite);