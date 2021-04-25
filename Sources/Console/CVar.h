#pragma once

#include <string>

enum CVarFlags {
    CVAR_NONE = 0,
    CVAR_CMD = 1 << 1, // Does not store a value, only a callback
    CVAR_INT = 1 << 2, // Stores an integer
    CVAR_FLOAT = 1 << 3, // Stores a float
    CVAR_STRING = 1 << 4, // Stores a string
    CVAR_BOOL = 1 << 5, // Stores a bool
    CVAR_CHEAT = 1 << 6, // Is a cheat, do not allow changes unless cheats are enabled
    CVAR_PERSIST = 1 << 7 // Persist the changes by saving to a config file
};

typedef std::string (*CmdCallback)(void);

class CVar {
public:
    CVar(std::string name, int defaultValue, int requestedFlags, std::string helpText = "");
    CVar(std::string name, float defaultValue, int requestedFlags, std::string helpText = "");
    CVar(std::string name, bool defaultValue, int requestedFlags, std::string helpText = "");
    CVar(std::string name, CmdCallback callback, int requestedFlags, std::string helpText = "");
    /*
	CVar(std::string name, std::string defaultValue, int requestedFlags);
	*/

    std::string get();
    std::string getHelp();
    bool set(std::string val);
    void set(bool val);

    int getInt();
    float getFloat();
    bool getBool();
    int flags = CVAR_NONE;

    bool hasFlag(CVarFlags flag);
    bool isInt();
    bool isFloat();
    bool isBool();
    bool isCmd();

private:
    void init(std::string name, int requestedFlags);

    int intVal;
    float floatVal;
    bool boolVal;
    std::string stringVal;
    CmdCallback cmdCallback;

    std::string varName;
    std::string help;
};
