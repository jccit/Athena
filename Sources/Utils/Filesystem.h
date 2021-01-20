#pragma once

#include <string>
#include <fstream>

std::string FS_ExeDir();
std::string FS_UserDir();
std::string FS_SaveDir();

std::ifstream FS_GetFile(std::string path);
char* FS_GetFileBytes(std::string path, size_t* size);
std::string FS_GetFileString(std::string path);

                                                 // ironic
std::ofstream FS_WriteStream(std::string path, bool nonBinary = false);
void FS_BytesToFile(std::string path, char* data, size_t size);
void FS_StringToFile(std::string path, std::string data);