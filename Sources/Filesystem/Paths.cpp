#include "pch.h"
#include "Paths.h"

std::string FS_ExeDir()
{
#ifdef _WIN32
	char buff[FILENAME_MAX];
	_getcwd(buff, FILENAME_MAX);
	std::string workingDir(buff);
	return workingDir;
#else
	return FS_UserDir();
#endif
}

std::string FS_UserDir()
{
#ifdef _WIN32
	LPWSTR path;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, NULL, &path);
	std::string utf8Path = WideToUTF8(path);
	return utf8Path;
#else
	const char *homedir;

	if ((homedir = getenv("HOME")) == NULL) {
		homedir = getpwuid(getuid())->pw_dir;
	}

	return std::string(homedir);
#endif
}

std::string FS_SaveDir()
{
#ifdef _WIN32
	LPWSTR path;
	SHGetKnownFolderPath(FOLDERID_SavedGames, KF_FLAG_CREATE, NULL, &path);
	std::string utf8Path = WideToUTF8(path);
	return utf8Path;
#else
	return FS_UserDir();
#endif
}