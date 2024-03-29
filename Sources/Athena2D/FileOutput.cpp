#define _CRT_SECURE_NO_WARNINGS

#include "pch.h"

#include "FileOutput.h"

#include <chrono>
#include <codecvt>
#include <ctime>
#include <iomanip>

#include <Filesystem/Paths.h>
#include <Filesystem/Raw.h>

FileOutput::FileOutput()
{
    const std::string userPath = FS_ConfigDir();
    filePath = FS_ResolvePath(userPath + "/game.log");
    logFile = FS_OpenFileWrite(filePath, true);
}

FileOutput::~FileOutput()
{
    if (logFile.is_open()) {
        logFile.close();
    }
}

void FileOutput::onPrint(std::string text, std::string source, OutputLevel level)
{
    std::string prefix = levelToString(level);

    auto now = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
    auto timer = std::chrono::system_clock::to_time_t(now);
    std::tm bt = *std::localtime(&timer);

    if (level == LEVEL_FATAL) {
        logFile << "--------------------------- FATAL ERROR!!!" << std::endl;
    }

    logFile << "[" << std::put_time(&bt, "%F %T");
    logFile << "." << std::setfill('0') << std::setw(3) << ms.count();
    logFile << std::put_time(&bt, "%z") << "][";
    logFile << prefix << "/" << source << "] " << text << std::endl;

    if (level == LEVEL_FATAL) {
        logFile << "---------------------------" << std::endl;
    }
}