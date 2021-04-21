#include "pch.h"
#include "Paths.h"

std::string FS_ExeDir()
{
	char buff[FILENAME_MAX];
	_getcwd(buff, FILENAME_MAX);
	std::string workingDir(buff);
	return workingDir;
}

std::string FS_UserDir()
{
	LPWSTR path;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, NULL, &path);
	std::string utf8Path = WideToUTF8(path);
	return utf8Path;
}

std::string FS_SaveDir()
{
	LPWSTR path;
	SHGetKnownFolderPath(FOLDERID_SavedGames, KF_FLAG_CREATE, NULL, &path);
	std::string utf8Path = WideToUTF8(path);
	return utf8Path;
}