#include "pch.h"
#include "Console.h"

#ifndef _DEBUG
static int maxLevel = LEVEL_INFO;
#else
static int maxLevel = LEVEL_VERBOSE;
#endif

Console& Console::getInstance()
{
	static Console instance;
	return instance;
}

Console::Console() = default;
Console::~Console() = default;

/**
 * \brief Shuts down the console and all outputs
 */
void Console::shutdown()
{
	for (auto out : outputs)
	{
		delete out;
	}
}

/**
 * \brief Register a CVar
 * \param name Var name
 * \param cvar CVar object
 */
void Console::registerVar(const std::string & name, CVar * cvar)
{
	cvars[name] = cvar;
}

/**
 * \brief Register an output to write the console to
 * \param output Output instance
 */
void Console::registerOutput(IOutput * output)
{
	outputs.push_back(output);
}

/**
 * \brief Runs a command, prints the result to output and returns the output
 * \param command Command to execute
 * \return Execution result
 */
std::string Console::exec(const std::string & command)
{
	std::string result = parse(command);

	print(result, "ConsoleOutput", LEVEL_INFO);
	return result;
}

std::string Console::parse(const std::string & command)
{
	auto split = command.find(' ');
	const std::string cvarName = command.substr(0, split);
	const std::string newVal = command.substr(split + 1);
	CVar* cvar = cvars[cvarName];

	if (cvar == nullptr)
	{
		// If cvar not found we're probably trying to run a command
		// In this case cvarName and newVal become the opcode and operand
		return runCommand(cvarName, newVal);
	}

	if (!newVal.empty() && cvarName != newVal)
	{
		// Setting cvar
		if (!cvar->set(newVal))
		{
			return "Failed to update cvar '" + cvarName + "'";
		}
	}

	return cvarName + " = " + cvar->get();
}

std::string Console::runCommand(const std::string & opcode, const std::string & operand)
{
	return "Command not found";
}

/**
 * \brief Print a line to the console and all outputs
 * \param text Message
 * \param source Name of system that created the message
 * \param level Severity of the message
 */
void Console::print(const std::string & text, const std::string & source, const OutputLevel level)
{
	if (level <= maxLevel) {
		for (IOutput* output : outputs)
		{
			output->onPrint(text, source, level);
		}
	}
}