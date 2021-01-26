#include "pch.h"
#include "CVar.h"
#include "Console.h"

#include <stdexcept>

/**
 * \brief Creates a CVar with an int type
 * \param name Name of CVar
 * \param defaultValue Default value
 * \param requestedFlags Any flags that apply to this CVar
 */
CVar::CVar(std::string name, int defaultValue, int requestedFlags)
{
	init(name, requestedFlags);
	intVal = defaultValue;
	flags |= CVAR_INT;
}

CVar::CVar(std::string name, float defaultValue, int requestedFlags)
{
	init(name, requestedFlags);
	floatVal = defaultValue;
	flags |= CVAR_FLOAT;
}

CVar::CVar(std::string name, bool defaultValue, int requestedFlags)
{
	init(name, requestedFlags);
	boolVal = defaultValue;
	flags |= CVAR_BOOL;
}

void CVar::init(std::string name, int requestedFlags)
{
	Console::getInstance().registerVar(name, this);
	flags = requestedFlags;
}

std::string CVar::get()
{
	std::string val = "";

	if (isInt())
	{
		val = std::to_string(getInt());
	}
	else if (isFloat())
	{
		val = std::to_string(getFloat());
	}
	else if (isBool())
	{
		val = boolVal ? "1" : "0";
	}

	return val;
}

bool CVar::set(std::string val)
{
	if (isInt())
	{
		try
		{
			int newVal = std::stoi(val);
			intVal = newVal;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
	if (isFloat())
	{
		try
		{
			float newVal = std::stof(val);
			floatVal = newVal;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}
	if (isBool())
	{
		try
		{
			bool newVal = val == "0" ? false : true;
			boolVal = newVal;
			return true;
		}
		catch (...)
		{
			return false;
		}
	}

	return false;
}


/**
 * \brief Returns the int value of the CVar, throws an error if not an int
 * \return CVar value as int
 */
int CVar::getInt()
{
	if (!isInt()) {
		throw new std::runtime_error("CVar is not an int");
	}
	return intVal;
}

float CVar::getFloat()
{
	if (!isFloat()) {
		throw new std::runtime_error("CVar is not a float");
	}
	return floatVal;
}

bool CVar::getBool()
{
	if (!isBool()) {
		throw new std::runtime_error("CVar is not a bool");
	}
	return boolVal;
}

bool CVar::hasFlag(CVarFlags flag)
{
	return (flags & flag) != 0;
}

bool CVar::isInt()
{
	return hasFlag(CVAR_INT);
}

bool CVar::isFloat()
{
	return hasFlag(CVAR_FLOAT);
}

bool CVar::isBool()
{
	return hasFlag(CVAR_BOOL);
}
