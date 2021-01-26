#pragma once

#include "CVar.h"
#include "IOutput.h"
#include <map>
#include <vector>
#include <string>

#define LOG(msg, src)			Console::getInstance().print(msg, src, OutputLevel::LEVEL_INFO)
#define LOG_WARN(msg, src)		Console::getInstance().print(msg, src, OutputLevel::LEVEL_WARNING)
#define LOG_ERROR(msg, src)		Console::getInstance().print(msg, src, OutputLevel::LEVEL_ERROR)
#define LOG_FATAL(msg, src)		Console::getInstance().print(msg, src, OutputLevel::LEVEL_FATAL)
#define LOG_DEBUG(msg, src)		Console::getInstance().print(msg, src, OutputLevel::LEVEL_DEBUG)
#define LOG_VERBOSE(msg, src)	Console::getInstance().print(msg, src, OutputLevel::LEVEL_VERBOSE)

typedef std::map<std::string, CVar*> CVarList;

class Console
{
public:
	static Console& getInstance();
	~Console();

	void shutdown();

	void registerVar(const std::string& name, CVar* cvar);
	void registerOutput(IOutput* output);

	std::string exec(const std::string& command);

	// Logging stuff
	void print(const std::string& text, const std::string& source, OutputLevel level);

	CVarList dumpVars(CVarFlags flags = CVAR_PERSIST);
	std::string getCfgFile();

private:
	Console();

	std::string parse(const std::string& command);
	std::string runCommand(const std::string& opcode, const std::string& operand);

	CVarList cvars;
	std::vector<IOutput*> outputs;
};

