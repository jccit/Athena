#include "pch.h"

#include "Console.h"

#include <algorithm>
#include <sstream>

#ifndef _DEBUG
static int maxLevel = LEVEL_INFO;
#else
static int maxLevel = LEVEL_VERBOSE;
#endif

// Internal cvars
std::string cmdHelp()
{
    std::string output = "\n";

    for (auto cvarPair : Console::getInstance().dumpVars(CVAR_NONE)) {
        output.append(cvarPair.first);
        output.push_back('\n');
    }

    return output;
}

CVar help = CVar("help", cmdHelp, 0);

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
    for (auto out : outputs) {
        out.reset();
    }
}

/**
 * \brief Register a CVar
 * \param name Var name
 * \param cvar CVar object
 */
void Console::registerVar(const std::string& name, CVar* cvar)
{
    cvars[name] = cvar;
}

/**
 * \brief Register an output to write the console to
 * \param output Output instance
 */
void Console::registerOutput(std::shared_ptr<IOutput> output)
{
    outputs.push_back(output);
}

/**
 * \brief Runs a command, prints the result to output and returns the output
 * \param command Command to execute
 * \return Execution result
 */
std::string Console::exec(const std::string& command)
{
    std::string result = parse(command);

    print(result, "ConsoleOutput", LEVEL_INFO);
    return result;
}

std::string Console::parse(const std::string& command)
{
    auto split = command.find(' ');
    const std::string cvarName = command.substr(0, split);
    const std::string newVal = command.substr(split + 1);
    CVar* cvar = cvars[cvarName];

    if (cvar == nullptr) {
        // If cvar not found we're probably trying to run a command
        // In this case cvarName and newVal become the opcode and operand
        return runCommand(cvarName, newVal);
    }

    if (!newVal.empty() && cvarName != newVal) {
        // Setting cvar
        if (!cvar->set(newVal)) {
            return "Failed to update cvar '" + cvarName + "'";
        }
    }

    std::string response = cvar->get();

    if (cvar->isCmd()) {
        return response;
    }

    return cvarName + " = " + response;
}

std::string Console::runCommand(const std::string& opcode, const std::string& operand)
{
    return "Command not found";
}

/**
 * \brief Print a line to the console and all outputs
 * \param text Message
 * \param source Name of system that created the message
 * \param level Severity of the message
 */
void Console::print(const std::string& text, const std::string& source, const OutputLevel level)
{
    if (level <= maxLevel) {
        for (std::shared_ptr<IOutput> output : outputs) {
            output->onPrint(text, source, level);
        }
    }
}

CVarList Console::dumpVars(CVarFlags flags)
{
    // If no flags specified, return all
    if (flags == CVAR_NONE) {
        return cvars;
    }

    CVarList filteredList;

    for (auto cvarPair : cvars) {
        if (cvarPair.second != NULL && cvarPair.second->hasFlag(flags)) {
            filteredList[cvarPair.first] = cvarPair.second;
        }
    }

    return filteredList;
}

std::string Console::getCfgFile()
{
    CVarList vars = dumpVars();
    std::ostringstream out;

    for (auto cvarPair : vars) {
        out << cvarPair.first;
        out << " ";
        out << cvarPair.second->get();
        out << std::endl;
    }

    return out.str();
}

std::vector<std::string> Console::autocomplete(std::string userInput)
{
    std::vector<std::string> results;

    for (auto cvarPair : cvars) {
        if (cvarPair.first.find(userInput) != std::string::npos) {
            results.push_back(cvarPair.first);
        }
    }

    std::sort(results.begin(), results.end(), [](std::string& s1, std::string& s2) { return s1.back() < s2.back(); });

    return results;
}
