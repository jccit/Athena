#pragma once

#include <string>

std::string WideToUTF8(std::wstring wstr);
std::wstring UTF8ToWide(std::string str);