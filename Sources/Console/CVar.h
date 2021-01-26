#pragma once
#include <string>

enum CVarFlags
{
	CVAR_NONE = 0,
	CVAR_INT = 1 << 1,		// Stores an integer
	CVAR_FLOAT = 1 << 2,	// Stores a float
	CVAR_STRING = 1 << 3,	// Stores a string
	CVAR_BOOL = 1 << 4,		// Stores a bool
	CVAR_CHEAT = 1 << 5,	// Is a cheat, do not allow changes unless cheats are enabled
	CVAR_PERSIST = 1 << 6	// Persist the changes by saving to a config file
};

class CVar
{
public:
	CVar(std::string name, int defaultValue, int requestedFlags);
	CVar(std::string name, float defaultValue, int requestedFlags);
	CVar(std::string name, bool defaultValue, int requestedFlags);
	/*
	CVar(std::string name, std::string defaultValue, int requestedFlags);
	*/

	std::string get();
	bool set(std::string val);

	int getInt();
	float getFloat();
	bool getBool();
	int flags = CVAR_NONE;

	bool hasFlag(CVarFlags flag);
	bool isInt();
	bool isFloat();
	bool isBool();

private:
	void init(std::string name, int requestedFlags);

	int intVal;
	float floatVal;
	bool boolVal;
	std::string stringVal;
};

