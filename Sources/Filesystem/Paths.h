#pragma once

#include <string>

std::string FS_ExeDir();
std::string FS_ConfigDir();
std::string FS_SaveDir();

std::string FS_ResolvePath(std::string path);