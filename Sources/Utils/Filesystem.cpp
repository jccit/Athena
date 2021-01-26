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

std::ifstream FS_OpenFileRead(std::string path, bool binary)
{
#ifdef WIN32
	std::wstring realPath = UTF8ToWide(path);
#else
	std::string realPath = path;
#endif

	std::ios::openmode openMode = binary ? std::ios::binary : 0;
	std::ifstream file(path, openMode);
	return file;
}

char* FS_ReadBytes(std::string path, size_t* size)
{
	std::ifstream file = FS_OpenFileRead(path);

	file.seekg(0, std::ios::end);
	size_t length = file.tellg();
	file.seekg(0, std::ios::beg);

	char* data = new char[length];
	file.read(data, length);

	file.close();

	*size = length;
	return data;
}

std::string FS_ReadString(std::string path)
{
	std::ifstream file = FS_OpenFileRead(path, false);
	std::string output((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
	file.close();
	
	return output;
}

std::ofstream FS_OpenFileWrite(std::string path, bool binary)
{
#ifdef WIN32
	std::wstring realPath = UTF8ToWide(path);
#else
	std::string realPath = path;
#endif

	std::ios::openmode openMode = binary ? std::ios::binary : 0;
	std::ofstream file(path, openMode);
	return file;
}

void FS_WriteBytes(std::string path, char* data, size_t size)
{
	std::ofstream file = FS_OpenFileWrite(path);
	file.write(data, size);	
	file.close();
}

void FS_WriteString(std::string path, std::string data)
{
	std::ofstream file = FS_OpenFileWrite(path, false);
	file << data;
	file.close();
}
