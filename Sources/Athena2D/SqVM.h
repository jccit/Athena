#pragma once

#include <simplesquirrel/simplesquirrel.hpp>

class SqVM
{
public:
	static SqVM& getInstance();
	~SqVM();

	void shutdown();
	
	void runScript(std::string path);

	ssq::VM* vm;

private:
	SqVM();
};

