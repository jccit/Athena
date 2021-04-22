#include "pch.h"
#include "Paths.h"
#include <filesystem>

std::string FS_ExeDir()
{
	std::string workingDir;
#ifdef _WIN32
	char buff[FILENAME_MAX];
	_getcwd(buff, FILENAME_MAX);
	workingDir = std::string(buff);
#else
	workingDir = FS_ConfigDir();
#endif

	return FS_ResolvePath(workingDir);
}

std::string FS_ConfigDir()
{
	std::string cfgPath;
#ifdef _WIN32
	LPWSTR path;
	SHGetKnownFolderPath(FOLDERID_LocalAppData, KF_FLAG_CREATE, NULL, &path);
	cfgPath = WideToUTF8(path) + "/Athena";
#else
	const char* homedir;

	if ((homedir = getenv("HOME")) == NULL) {
		homedir = getpwuid(getuid())->pw_dir;
	}

	cfgPath = std::string(homedir) + "/.local/Athena";
#endif

	return FS_ResolvePath(cfgPath);
}

std::string FS_SaveDir()
{
#ifdef _WIN32
	LPWSTR path;
	SHGetKnownFolderPath(FOLDERID_SavedGames, KF_FLAG_CREATE, NULL, &path);
	std::string utf8Path = WideToUTF8(path);
	return utf8Path;
#else
	return FS_ConfigDir();
#endif
}

std::string FS_ResolvePath(std::string path)
{
	std::filesystem::path realPath(path);
	return realPath.string();
}
