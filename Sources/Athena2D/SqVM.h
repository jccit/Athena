#pragma once

#include <simplesquirrel/simplesquirrel.hpp>
#include <string>

class SqVM
{
public:
	SqVM();
	~SqVM();

	void runScript(std::string path);
private:
	ssq::VM* vm;
};

