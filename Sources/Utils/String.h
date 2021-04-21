#pragma once

#include <string>

#ifdef _WIN32
std::string WideToUTF8(std::wstring wstr);
std::wstring UTF8ToWide(std::string str);
#endif