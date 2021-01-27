#pragma once

#include <string>

/**
 * \brief Severity level of the message, the higher the number the more verbose logging level is required
 */
enum OutputLevel
{
	LEVEL_FATAL = 0,
	LEVEL_ERROR = 1,
	LEVEL_WARNING = 2,
	LEVEL_INFO = 3,
	LEVEL_DEBUG = 4,
	LEVEL_VERBOSE = 5
};

/**
 * \brief Interface for console outputs
 */
class IOutput
{
public:
	/**
	 * \brief Called whenever the console has printed a message
	 * \param text Message
	 * \param source Name of system that created the message
	 * \param level Severity of the message
	 */
	virtual void onPrint(std::string text, std::string source, OutputLevel level) = 0;

protected:
	static std::string levelToString(OutputLevel level)
	{
		std::string prefix;

		switch (level)
		{
		case LEVEL_FATAL:
			prefix = "F";
			break;
		case LEVEL_ERROR:
			prefix = "E";
			break;
		case LEVEL_WARNING:
			prefix = "W";
			break;
		case LEVEL_DEBUG:
			prefix = "D";
			break;
		case LEVEL_VERBOSE:
			prefix = "V";
			break;
		case LEVEL_INFO:
			prefix = "I";
			break;
		}

		return prefix;
	}
};