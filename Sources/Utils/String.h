#pragma once

#include <string>

#ifdef _WIN32
#include <direct.h>
#include <ShObjIdl.h>

std::string WideToUTF8(std::wstring wstr);
std::wstring UTF8ToWide(std::string str);
#endif