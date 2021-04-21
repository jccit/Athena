#include "pch.h"
#include "String.h"

#ifdef _WIN32
std::string WideToUTF8(std::wstring wstr)
{
	if (wstr.empty()) return std::string();

	int sizeRequired = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], static_cast<int>(wstr.size()), nullptr, 0, nullptr, nullptr);
	std::string utf8Str(sizeRequired, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], static_cast<int>(wstr.size()), &utf8Str[0], sizeRequired, NULL, NULL);

	return utf8Str;
}

std::wstring UTF8ToWide(std::string str)
{
	if (str.empty()) return std::wstring();

	int sizeRequired = MultiByteToWideChar(CP_UTF8, 0, &str[0], static_cast<int>(str.size()), nullptr, 0);
	std::wstring wstr(sizeRequired, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], static_cast<int>(str.size()), &wstr[0], sizeRequired);

	return wstr;
}
#endif