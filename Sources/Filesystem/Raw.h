#pragma once

#include <fstream>
#include <string>

std::ifstream FS_OpenFileRead(std::string path, bool binary = true);
char* FS_ReadBytes(std::string path, size_t* size);
std::string FS_ReadString(std::string path);

std::ofstream FS_OpenFileWrite(std::string path, bool binary = true);
void FS_WriteBytes(std::string path, char* data, size_t size);
void FS_WriteString(std::string path, std::string data);