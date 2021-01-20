#include "pch.h"
#include "Filesystem.h"
#include "String.h"

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

std::ifstream FS_GetFile(std::string path)
{
#ifdef WIN32
	std::wstring realPath = UTF8ToWide(path);
#else
	std::string realPath = path;
#endif

	std::ifstream file(path, std::ios::binary);
	return file;
}

char* FS_GetFileBytes(std::string path, size_t* size)
{
	std::ifstream file = FS_GetFile(path);

	file.seekg(0, std::ios::end);
	size_t length = file.tellg();
	file.seekg(0, std::ios::beg);

	char* data = new char[length];
	file.read(data, length);

	file.close();

	*size = length;
	return data;
}

std::string FS_GetFileString(std::string path)
{
	size_t size = 0;
	char* buffer = FS_GetFileBytes(path, &size);

	std::string output = std::string(buffer, size);
	delete buffer;
	return output;
}

std::ofstream FS_WriteStream(std::string path, bool nonBinary)
{
#ifdef WIN32
	std::wstring realPath = UTF8ToWide(path);
#else
	std::string realPath = path;
#endif

	std::ios::openmode openMode = nonBinary ? 0 : std::ios::binary;
	std::ofstream file(path, openMode);
	return file;
}

void FS_BytesToFile(std::string path, char* data, size_t size)
{
	std::ofstream file = FS_WriteStream(path);
	file.write(data, size);	
	file.close();
}

void FS_StringToFile(std::string path, std::string data)
{
	std::ofstream file = FS_WriteStream(path, true);
	file << data;
	file.close();
}
