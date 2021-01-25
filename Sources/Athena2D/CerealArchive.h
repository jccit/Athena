#pragma once
#include <cereal/archives/json.hpp>

#define CEREAL_INPUT cereal::JSONInputArchive
#define CEREAL_OUTPUT cereal::JSONOutputArchive