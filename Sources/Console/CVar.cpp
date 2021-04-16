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
CVar::CVar(std::string name, int defaultValue, int requestedFlags, std::string helpText)
{
	init(name, requestedFlags);
	intVal = defaultValue;
	flags |= CVAR_INT;
	help = helpText;
}

CVar::CVar(std::string name, float defaultValue, int requestedFlags, std::string helpText)
{
	init(name, requestedFlags);
	floatVal = defaultValue;
	flags |= CVAR_FLOAT;
	help = helpText;
}

CVar::CVar(std::string name, bool defaultValue, int requestedFlags, std::string helpText)
{
	init(name, requestedFlags);
	boolVal = defaultValue;
	flags |= CVAR_BOOL;
	help = helpText;
}

CVar::CVar(std::string name, CmdCallback callback, int requestedFlags, std::string helpText)
{
	init(name, requestedFlags);
	cmdCallback = callback;
	flags |= CVAR_CMD;
}

void CVar::init(std::string name, int requestedFlags)
{
	Console::getInstance().registerVar(name, this);
	flags = requestedFlags;
	varName = name;
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
	else if (isCmd())
	{
		if (cmdCallback) {
			val = cmdCallback();
		}
	}

	return val;
}

std::string CVar::getHelp()
{
	std::string val = "";

	if (help != "") {
		val += "\n";
		val += varName;
		val += " - ";
		val += help;
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

bool CVar::isCmd()
{
	return hasFlag(CVAR_CMD);
}
